{-# LANGUAGE TemplateHaskell #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE MultiParamTypeClasses #-}

module Main (main) where

import           Debug.Trace    

import           Control.Monad
import           Data.Monoid
import           Data.Functor.Identity
import qualified Data.ByteString.Lazy as BS
import           Data.String
import           Data.ByteString.Builder
import           Data.List
import           Data.Int
import           System.IO
import           System.Environment
import           System.Directory
import           System.FilePath
import           Text.Parsec
import qualified Text.Parsec.Token as Token

-- Note:
-- 1.can't handle with macro

-- compiler config
totalConsN = 0
version = 
    "steak language compiler version 1.0\n" ++
    "MIT License Copyright (c) 2017 Long Jinwei\n" ++
    "more information at https://github.com/nicekingwei/steak"
help = 
    "steak language compiler 1.0\n" ++
    "Usage: \n"++
    "* steak file:      compile the source file and print the object code to stdout\n" ++ 
    "* steak dirctory:  search the directory recursively and compile all *.stk.cpp,*.stk.h,*.stk.hpp to *.cpp,*.h,*.hpp\n" ++
    "* steak --version: version and license\n" ++
    "* steak --help:    help"


-- Builder utils
instance Show Builder where
    show b = map (toEnum.fromEnum) $ BS.unpack (toLazyByteString b)

instance Eq Builder where
    a==b = (toLazyByteString a) == (toLazyByteString b)

class (Show a)=>Encodable a where
    encode::a->Builder
    encode = string7 . show

instance Encodable Char where
    encode = char7

instance Encodable String where
    encode = fromString

instance Encodable BS.ByteString where
    encode = lazyByteString 

instance Encodable Double
instance Encodable Integer
instance Encodable Int64

instance (Encodable a,Encodable b)=>Encodable (Either a b) where
    encode x = case x of Left  y -> encode y
                         Right z -> encode z


-- ByteStream
data ByteStream = ByteStream {
    pos::Int64,
    len::Int64,
    buffer::BS.ByteString
} deriving (Eq,Show)

instance (Monad m) => Stream ByteStream m Char where
    uncons s = let p = pos s in return $ if p==len s then Nothing else Just ((toEnum . fromEnum) $ BS.index (buffer s) p , s {pos=p+1} )

toByteStream::BS.ByteString -> ByteStream
toByteStream s = ByteStream 0 (BS.length s) s


-- Other utils

toByteString::(Enum a)=>[a]->BS.ByteString
toByteString = BS.pack . map (toEnum.fromEnum)

slice::(Int64,Int64)->BS.ByteString->Builder
slice (s,t) src = encode $ BS.take (t-s) (BS.drop s src)

debugLevel x = do
    t<-getBraceLevel
    ts<-getResetLevels
    p<-getPosition
    trace (show t ++ " " ++ show ts ++ " " ++ show (sourceLine p)) x

-- Code generator 
transNestedComment::Builder->Builder
transNestedComment b =  let s = toLazyByteString b 
                            len = fromIntegral (BS.length s)::Int64
                        in snd $ foldl (\(p,acc) i->
                            if i==len then
                                (p , acc <> (slice (p,len) s))
                            else if and [BS.index s (i-1) == ((toEnum.fromEnum) '*'),BS.index s i == ((toEnum.fromEnum) '/')] then
                                (i , acc <> (slice (p,i-1) s) <> encode ' ')
                            else
                                (p , acc)) (0,mempty) [1..len]

unsplitB::Char->[Builder]->Builder
unsplitB _ [] = mempty
unsplitB s xs = let ss = encode s in foldr1 (\x acc->mconcat [x,ss,acc]) xs

unTwoWords::(Builder,Builder)->Builder
unTwoWords (x,y) = x <> encode ' ' <> y 

wrapAngle::Builder->Builder
wrapAngle b = encode '<' <> b <> encode '>'

wrapBrace::Builder->Builder
wrapBrace b = encode '{' <> b <> encode '}'

wrapParenthese::Builder->Builder
wrapParenthese b = encode '(' <> b <> encode ')'

wrapLazyFun::Builder->Builder->Builder
wrapLazyFun ret b = encode "return steak::lazy_call(std::function<" <> ret <> encode "()> ( [=](){" <> b <> encode "} ) );"


-- copy from http://hackage.haskell.org/package/parsec-3.1.11/docs/src/Text.Parsec.Language.html#javaStyle
cppStyle::Token.GenLanguageDef ByteStream st Identity
cppStyle = Token.LanguageDef
        { Token.commentStart   = "/*"
        , Token.commentEnd     = "*/"
        , Token.commentLine    = "//"
        , Token.nestedComments = True
        , Token.identStart     = letter <|> char '_'
        , Token.identLetter    = alphaNum <|> oneOf "_"
        , Token.opStart        = oneOf ":!#$%&*+./<=>?@\\^|-~;(),[]"
        , Token.opLetter       = oneOf ":!#$%&*+./<=>?@\\^|-~"
        , Token.reservedNames  = ["case","default"]
        , Token.reservedOpNames= ["{}"]
        , Token.caseSensitive  = False
        }

-- simple tokenizer
cppToken = Token.makeTokenParser cppStyle

-- abstract syntax tree
data Constructors = MkCons {
    retType::Builder,                        -- return type                 Maybe<a>
    retTypeArgs::[Builder],                  -- parameters of return type   a
    consName::Builder,                       -- constructor name            Just
    argTypes::[Builder]                      -- arguments types             a
} deriving (Show)

data ParserStates = MkParserStates {
    braceLevel:: Int,
    resetLevels::[Int]
}

type Parser = ParsecT ByteStream ParserStates Identity

emptyState::ParserStates
emptyState = MkParserStates 0 []

-- states : verb + state
getBraceLevel::Parser Int
getBraceLevel = do
    MkParserStates n _<- getState
    return n

incBraceLevel::Parser ()
incBraceLevel = modifyState (\c->c{braceLevel=braceLevel c+1})

decBraceLevel::Parser ()
decBraceLevel = modifyState (\c->c{braceLevel=braceLevel c-1})

getResetLevels::Parser [Int]
getResetLevels = do
    MkParserStates _ xs<-getState
    return xs

topResetLevel::Parser Int
topResetLevel = do
    MkParserStates _ xs <- getState
    if null xs then
        fail "error: unknown error"
    else
        return (head xs)

popResetLevel::Parser ()
popResetLevel = do
    MkParserStates _ xs <- getState
    if null xs then
        fail "error: unknown error"
    else
        modifyState (\c->c {resetLevels = tail xs })

pushResetLevel::Parser ()
pushResetLevel = do
    MkParserStates t xs <- getState
    modifyState (\c->c{resetLevels = t:xs})    

-- parser combinator: no extra space at end
consumeWhite::Parser a->Parser a
consumeWhite p = do
    x<-p
    optWhiteSpace
    return x


lbraceS::Parser Builder
lbraceS = do
    charW '{'
    incBraceLevel
    return $ encode '{'

rbraceS::Parser Builder
rbraceS = do
    charW '}'
    decBraceLevel    
    return $ encode '}'

encodeM::(Encodable a)=>Parser a->Parser Builder
encodeM p = p>>=return . encode 

commaSep::Parser a->Parser [a]
commaSep = Token.commaSep cppToken

commaSep1::Parser a->Parser [a]
commaSep1 = Token.commaSep1 cppToken

charW::Char->Parser Builder
charW = encodeM.consumeWhite.char

stringW::String->Parser Builder
stringW = encodeM.consumeWhite.string

whiteSpace::Parser Builder
whiteSpace = do
    Token.whiteSpace cppToken
    return mempty

optWhiteSpace::Parser ()
optWhiteSpace = optional whiteSpace

identifier::Parser Builder
identifier = encodeM.consumeWhite $ Token.identifier cppToken

operator::Parser Builder
operator = encodeM.consumeWhite $ Token.operator cppToken

parenthese::Parser a->Parser a
parenthese = consumeWhite . between (charW '(') (charW ')')

angleBracket::Parser a->Parser a
angleBracket = consumeWhite . between (charW '<') (charW '>')

brace::Parser a->Parser a
brace = consumeWhite . between (charW '{') (charW '}')

braceS::Parser a->Parser a
braceS = consumeWhite . between (pushResetLevel>>lbraceS) (endBraceS)

endBraceS::Parser Builder
endBraceS = do
    c<-charW '}'
    l<-getBraceLevel
    t<-topResetLevel
    if l==t+1 then do
        decBraceLevel
        popResetLevel
        return c
    else
        fail ""

endBrace::Parser Builder
endBrace = do
    c<-charW '}'
    l<-getBraceLevel
    t<-topResetLevel
    if l==t+1 then do
        return c
    else
        fail ""

literal::Parser Builder
literal = consumeWhite $ 
    (encodeM $ Token.stringLiteral cppToken) <|>
    (encodeM $ Token.charLiteral cppToken) <|>
    (encodeM $ Token.naturalOrFloat cppToken)

reserved::String->Parser Builder
reserved s = consumeWhite $ do 
    Token.reserved cppToken s
    return (encode s)
    

caseKeyWords::Parser Builder
caseKeyWords = reserved "case" <|> reserved "default"


cppType::Parser (Builder,[Builder])
cppType = do
    m<-identifier
    xs<-option [] $ angleBracket (commaSep1 identifier)
    if null xs then 
        return (m,xs)
    else
        return (mconcat [m,encode '<',unsplitB ',' xs,encode '>'],xs)

anyTokens::Parser Builder
anyTokens = choice [identifier,operator,literal,lbraceS,rbraceS,caseKeyWords]

dataclassHead::Parser Builder
dataclassHead = do
    optional $ do
        stringW "template"
        angleBracket $ commaSep1 $ do
            cppType
            identifier
    reserved "dataclass"

dataclass::Parser Builder
dataclass = do
    -- Parse
    ByteStream start _ buf <- getInput
    tempDef<-try (do
        tempDef<-option [] $ do
            stringW "template"
            angleBracket $ commaSep1 $ do
                (t,_)<-cppType
                i<-identifier
                return (t,i)
        reserved "dataclass"
        return tempDef)
    dataName<-identifier
    consLst<-braceS $ many $ do
        (t,as)<-cppType
        n<-identifier
        args<-parenthese (commaSep cppType)
        charW ';'
        return $ MkCons {retType=t,retTypeArgs=as,consName=n,argTypes=map fst args}
    ByteStream end _ _ <- getInput    
    charW ';'
    
    -- Code generator
    let 
        genRegCons c = let name = consName c in encode "namespace steak_constructors{struct " <> name <> encode "{static constexpr const char* consname=\"" <> name <> encode "\";};};\n"
        genCaseClass c  =   let as = argTypes c
                                name = consName c
                            in  encode "steak::case_class_t" <>
                                wrapAngle (unsplitB ',' ( (encode "steak_constructors::" <> name) :as))
        genConsTempVars xs = unsplitB ',' $ map unTwoWords xs             
        genConsFunDefs c =  let name = consName c
                                rt = retType c
                                ras = retTypeArgs c
                                as = argTypes c
                                n = length as
                                tbs = foldl (\acc _->[x:y|y<-acc,x<-[True,False]]) [[]] [0..n]
                                pbs = do
                                    x<-[False]
                                    y<-if n==0 then [[]] else [replicate n False]
                                    return (x:y)
                                
                                fas = do
                                    (t,p)<-tempDef
                                    a<-ras
                                    guard (a==p)
                                    return (t,p)

                                temp = if null fas then mempty else encode "template" <> wrapAngle (genConsTempVars fas)
                                
                                -- bs:True for strict,False for lazy
                                genCons (s:bs) = let cs = zip3 bs as ([1..]::[Int64]) in
                                    temp <> encode "inline "  <>
                                    (if s then rt else (encode "steak::lazy_type_t<" <> rt <> encode '>')) <> encode ' ' <>
                                    name <> 
                                    (wrapParenthese.unsplitB ',') (map (\(b,a,i)->if b then 
                                                encode "const " <> a <> encode "& v" <> encode i else 
                                                encode "steak::lazy_type_t<" <> a <> encode "> v" <> encode i) cs) <>
                                    (wrapBrace . (if s then id else wrapLazyFun rt)) (
                                        encode "return " <> genCaseClass c <> ( (wrapParenthese.unsplitB ',') (map (\(b,a,i)-> if b then
                                                    encode 'v' <> encode i else
                                                    encode 'v' <> encode i <> encode ".get()") cs) ) <> encode ";" )

                            in  (unsplitB '\n' $ map genCons pbs)            
                                    
        sTotTemp = if null tempDef then mempty else encode "template" <> wrapAngle (genConsTempVars tempDef)                         
        sCaseClass =  (wrapAngle . unsplitB ',' . map genCaseClass) consLst  

        code = 
            encode "/*\n" <> transNestedComment (slice (start,end) buf) <> encode ";\n*/\n" <>
            mconcat (map genRegCons consLst) <> 
            sTotTemp <> encode "struct " <> dataName <> encode ";\n" <>
            sTotTemp <> encode "struct " <> dataName <> encode ":public steak::data_class_t" <> sCaseClass <>
            encode "\n{\n\t" <> dataName <> encode "(){}\n\ttemplate<typename...K>" <> dataName <> encode "(K...args):steak::data_class_t" <> sCaseClass <> encode "(args...){}\n};\n" <>
            (mconcat $ map (<> encode '\n') (map genConsFunDefs consLst)) <> encode '\n'
    return code

matchExpr::Parser Builder
matchExpr = try $ do
    cons<-identifier
    parenthese $ do
        paras<-option mempty $ commaSep (matchExpr <|> identifier)
        let code = encode "steak::attach_ghost<steak_constructors::" <> cons <> encode ">" <>
                    encode "(steak::forward_and_zip(" <> unsplitB ',' paras <> encode "))"
        return code

matchHead::Parser Builder
matchHead = do
    stringW "match"
    parenthese $ identifier

match::Parser Builder
match = do
    -- Parse
    ByteStream start _ buf <- getInput    
    var<-try matchHead
    xs<-braceS $ many $ do
        notFollowedBy endBrace
        k<-caseKeyWords
        mexp<-if k==encode "case" then matchExpr else return mempty
        charW ':'
        bs<-many ((codeBlock (endBrace <|> caseKeyWords)) <|> match)
        return (mexp,mconcat bs)
    ByteStream end _ _ <- getInput
        
    -- Code Generator
    let blocks = zip xs ([1..]::[Int64])
        code =
            encode "\n/*\n" <> slice (start,end) buf <> encode "\n*/\n" <>
            wrapBrace (
                encode "\nint match_num=0;\nauto match_var__=" <> var <> encode ".get();\nif(0){;" <>
                mconcat (map (\((expr,_),i)->if expr == mempty then mempty else 
                    encode "}\nelse if(match_var__.match(" <> expr <> encode ")){match_num=" <> encode i <> encode ';') blocks) <>
                encode "}\nswitch(match_num)\n{\n" <> 
                mconcat (map (\((expr,block),i) -> (if expr == mempty then encode "default:\n" else encode "case " <> encode i <> encode ":\n") <> block <> encode '\n') blocks) <>
                encode "}\n"
            )
    return code

codeBlock::Parser Builder->Parser Builder
codeBlock endP = do
    ByteStream start _ buf <- getInput
    many1 $ do
        notFollowedBy (dataclassHead <|> matchHead <|> endP)
        anyTokens
    ByteStream end _ _ <- getInput
    if end==start then
        fail ""
    else
        return (slice (start,end) buf)
    
            
globalParser::Parser Builder
globalParser = do
    whiteSpace
    xs<-many ((codeBlock (fail "")) <|> dataclass <|> match)
    return $ mconcat xs

compile::String->Handle->Handle->IO ()
compile name hin hout = do
    src<-BS.hGetContents hin
    case runParser globalParser emptyState name (toByteStream src) of
        Left  x -> hPutStrLn stderr (show x)
        Right y -> BS.hPutStr hout (toLazyByteString y)
    return ()

judgeFile::FilePath->IO (Either FilePath [FilePath])
judgeFile f = do
    b1<-doesDirectoryExist f
    if b1 then do
        fs<-getDirectoryContents f
        return (Right (map (\s->f </> s) $ filter (\c->and [c/=".",c/=".."]) fs))
    else do
        b2<-doesFileExist f
        if b2 then do
            let (fn,ext)=splitExtensions f
                (stk,cpp) = splitAt 5 ext
            if and [stk == ".stk.",or [cpp=="cpp",cpp=="hpp",cpp=="h"]] then
                return (Left (addExtension fn cpp))
            else
                return (Left "")
        else
            return (Left "")

compilePathOrDir::FilePath->IO ()
compilePathOrDir fs = do
    let search f = do
            jf<-judgeFile f
            case jf of
                Left file->when (null file==False) $ do
                    hin<-openFile f ReadMode
                    hout<-openFile file WriteMode
                    compile f hin hout
                    hClose hout
                    hClose hin
                Right dir-> sequence_ (map search dir)    
            return ()

    b1<-doesFileExist fs
    b2<-doesDirectoryExist fs
    if b1 then do
        hin<-openFile fs ReadMode
        compile fs hin stdout
        hClose hin
    else if b2 then
        search fs
    else do
        hPutStrLn stderr "fatal error: no such file or directory."
        putStrLn help
    return ()


main = do
    args<-getArgs
    if null args then
        hPutStrLn stderr "fatal error: no input file or directory."
    else do
        let arg = head args
        if arg == "--version" then
            putStrLn version
        else if arg == "--help" then
            putStrLn help
        else
            compilePathOrDir arg
    return ()