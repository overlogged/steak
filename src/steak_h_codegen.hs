import           Text.Printf
import           Data.Monoid

totalConsN = 5

mapJoin::(a->String)->[a]->String
mapJoin f xs@(_:_) = foldl1 (\acc s->acc++","++s) (map f xs)
mapJoin _ []       = []

unsplit::Char->[String]->String
unsplit _ [] = mempty
unsplit ss xs = foldr1 (\x acc->mconcat [x,[ss],acc]) xs

genFunApply::Int->String
genFunApply n =
    let macro = printf "\t#define Apply%d(f,%s) steak::lazy_apply%d(std::function(f),%s)\n" n ss n ss where ss=mapJoin (printf "v%d") [1..n]
        lazy  =  "\t/**\n" ++
            printf "\t*  @brief nested lazy apply%d\n" n ++
            "\t*/\n" ++
            "\ttemplate<typename T0," ++ mapJoin (printf "typename T%d") [1..n] ++ ">\n" ++
            printf "\tsteak::lazy_type_t<T0> lazy_apply%d(" n ++ printf "std::function<T0(%s)> f," (mapJoin (printf "T%d") [1..n]) ++
            mapJoin (\i->printf "steak::lazy_type_t<T%d> t%d" i i) [1..n] ++ ")\n" ++
            "\t{\n" ++
            printf "\t\treturn std::function([=](){return f(%s);});\n" (mapJoin (printf "t%d.eval()") [1..n]) ++
            "\t}\n\n"
        strit =  "\t/**\n" ++
            printf "\t*  @brief weak lazy apply%d\n" n ++
            "\t*/\n" ++
            "\ttemplate<typename T0," ++ mapJoin (printf "typename T%d") [1..n] ++ ">\n" ++
            printf "\tsteak::lazy_type_t<T0> lazy_apply%d(" n ++ printf "std::function<T0(%s)> f," (mapJoin (printf "T%d") [1..n]) ++
            mapJoin (\i->printf "const T%d& v%d" i i) [1..n] ++ ")\n" ++
            "\t{\n" ++
            printf "\t\treturn std::function([=](){return f(%s);});\n" (mapJoin (printf "v%d") [1..n]) ++
            "\t}\n\n"
    in macro ++ lazy ++ strit


genCons::Int->String
genCons n =
    let bs = if n<=totalConsN then
                foldl (\acc _->[x:y|y<-acc,x<-[True,False]]) [[]] [0..n]
             else do
                x<-[True,False]
                y<-if n==0 then [[]] else [replicate n True,replicate n False]
                return (x:y)
        wrapLazyFun b =  "return std::function([=](){" <> b <> "});"
        types = concatMap (printf ",t%d") [1 .. n]::String
        genCon (s:bs) = let cs = zip3 bs (map (\i->"t" <> show i) [1..]) [1..] in
            "T inline "  <>
            (if s then "ret " else "steak::lazy_type_t<ret> ") <>
            (if s then "name" else "name##_") <> 
            "(" <>
            (unsplit ',') (map (\(b,a,i)->if b then 
                        "const " <> a <> "& v" <> show i else 
                        "steak::lazy_type_t<" <> a <> "> v" <> show i) cs) <>
            "){" <>
            (if s then id else wrapLazyFun)(
                      "return " <> printf "steak::case_class_t<steak_constructors::name%s>" types <> "(" <> ( (unsplit ',') (map (\(b,a,i)-> if b then
                            "v" <> show i else
                            "v" <> show i <> ".eval()") cs) ) <> ");" ) <> "}\\\n"
                        

        macro = printf "\t#define Cons%d(T,name%s,ret)\\\n" n types  ++
                (mconcat $ map genCon bs) ++ "\n"
                

    in macro

genVMacros::Int->String
genVMacros n
    |n>0 = printf "\t\t#define V%s template<%s>\n" (take n ['a'..]) (mapJoin (printf "typename %c") (take n ['a'..]))
    |n==0 = "\t\t#define V\n"

main = do
    let n = 20
    let head =  "#ifndef _STEAK_H_\n#define _STEAK_H_\n" ++
                "/**\n"++
                " *  @brief  a functional library for cpp\n"++
                " *  @author Nicekingwei(Long Jinwei)\n"++
                " */ \n"++
                "#include <iostream>\n"++
                "#include <exception>\n"++
                "#include <functional>\n"++
                "#include <memory>\n"++
                "#include <variant>\n"++
                "#include \"runtime.h\"\n\n" ++ 
                "#define With(x) if(1){auto match_var=x.eval();if(0){;\n" ++
                "#define Case(name,...) }else if(match_var.match(steak::attach_ghost<steak_constructors::name>(steak::forward_and_zip(__VA_ARGS__)))){;\n" ++
                "#define Default }else{;\n" ++
                "#define EndWith() }}\n" ++
                "#define UnZip(name,...) steak::attach_ghost<steak_constructors::name>(steak::forward_and_zip(__VA_ARGS__))\n" ++                   
                "#define Data(T,name,...) T struct name;T struct name:public steak::data_class_t<__VA_ARGS__>{name(){} template<typename...K>name(K...args):steak::data_class_t<__VA_ARGS__>(args...){}};\n" ++
                "#define RegCons(name) namespace steak_constructors{struct name {static constexpr const char* consname=#name;};};\n"++               
                "#define RealType(name,...) steak::cal_cons_type<steak_constructors::name>::R<__VA_ARGS__>\n" ++    
                "#define DerivingShow(T,name) \\\nT std::ostream& operator << (std::ostream& out,name& x)\\\n{\\\n\treturn x.show(out);\\\n}\n\n"
    putStr head
    putStr "namespace steak\n{\n"
    putStr $ foldl1 (++) $ map genFunApply [1..n]
    putStr $ foldl1 (++) $ map genCons [0..n]
    putStr $ foldl1 (++) $ map genVMacros [0..n]
    putStr "};\n#endif"
