import           Text.Printf
import           Data.Monoid

mapJoin :: (a -> String) -> [a] -> String
mapJoin f xs@(_ : _) = foldl1 (\acc s -> acc ++ "," ++ s) (map f xs)
mapJoin _ []         = []

unsplit :: Char -> [String] -> String
unsplit _  [] = mempty
unsplit ss xs = foldr1 (\x acc -> mconcat [x, [ss], acc]) xs

genCons :: Int -> String
genCons n =
    let
        wrapLazyFun b = "return steak::lazy_call(std::function<ret()> ( [=](){" <> b <> "} ) );"
        types = concatMap (printf ",t%d") [1 .. n] :: String
        genCon
            = let type_var = zip (map (\i -> "t" <> show i) [1 .. n]) [1 .. n]
              in
                  "T inline steak::lazy_type_t<ret> name("
                  <> (unsplit ',')
                         (map
                             (\(a, i) ->
                                 "steak::lazy_type_t<" <> a <> "> v" <> show i
                             )
                             type_var
                         )
                  <> "){"
                  <> wrapLazyFun
                         (  "return ret("
                         <> printf
                                "steak::case_class_t<steak_constructors::name%s>"
                                types
                         <> "("
                         <> ((unsplit ',')
                                (map (\i -> "v" <> show i <> ".get()")
                                     [1 .. n]
                                )
                            )
                         <> "));"
                         )
                  <> "}\\\n"


        macro =
            printf "\t#define Cons%d(T,name,ret%s)\\\n" n types
                ++ genCon
                ++ "\n"
    in
        macro

genVMacros :: Int -> String
genVMacros n
    | n > 0 = printf "\t\t#define V%s template<%s>\n"
                     (take n ['a' ..])
                     (mapJoin (printf "typename %c") (take n ['a' ..]))
    | n == 0 = "\t\t#define V\n"

main = do
    let n = 20
    let
        head =
            "#ifndef _STEAK_H_\n#define _STEAK_H_\n"
                ++ "/**\n"
                ++ " *  @brief  a functional library for cpp\n"
                ++ " *  @author nicekingwei(Long Jinwei)\n"
                ++ " */ \n"
                ++ "#include <iostream>\n"
                ++ "#include <exception>\n"
                ++ "#include <functional>\n"
                ++ "#include <memory>\n"
                ++ "#include <variant>\n"
                ++ "#include \"runtime.h\"\n\n"
                ++ "#define With(x) if(1){auto match_var=x.get();if(0){;\n"
                ++ "#define Case(name,...) }else if(match_var.match(steak::attach_ghost<steak_constructors::name>(steak::forward_and_zip(__VA_ARGS__)))){;\n"
                ++ "#define Default }else{;\n"
                ++ "#define EndWith() }}\n"
                ++ "#define UnZip(name,...) steak::attach_ghost<steak_constructors::name>(steak::forward_and_zip(__VA_ARGS__))\n"
                ++ "#define Data(T,name,...) T struct name;T struct name:public steak::data_class_t<__VA_ARGS__>{name(){} template<typename...K>name(K...args):steak::data_class_t<__VA_ARGS__>(args...){}};\n"
                ++ "#define RegCons(name) namespace steak_constructors{struct name {static constexpr const char* consname=#name;};};\n"
                ++ "#define RealType(name,...) steak::cal_cons_type<steak_constructors::name>::R<__VA_ARGS__>\n"
                ++ "#define DerivingShow(T,name) \\\nT std::ostream& operator << (std::ostream& out,name& x)\\\n{\\\n\treturn x.show(out);\\\n}\n\n"
    putStr head
    putStr "namespace steak\n{\n"
    putStr $ foldl1 (++) $ map genCons [0 .. n]
    putStr $ foldl1 (++) $ map genVMacros [0 .. n]
    putStr "};\n#endif"
