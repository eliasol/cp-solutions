import Foreign.Marshal.Utils ( fromBool )

solve :: Int -> [Int] -> [Int] -> Int -> Int
solve _ [] [] _ = 0
solve x (l:ls) [] sum = fromBool (sum == x) + solve x ls [] (sum - l)
solve x (l:ls) (r:rs) sum
    | sum >= x = fromBool (sum == x) + solve x ls (r:rs) (sum - l)
    | otherwise = solve x (l:ls) rs (sum + r)

main :: IO ()
main = getLine >>= (\x -> getLine >>= print . (\l -> solve x l l 0) . map read . words) . (!!1) . map read . words
