solve :: Int -> Int -> [Int] -> Int
solve bst ps [] = ps - bst
solve bst ps (x : xl) = max (solve (min bst ps) (ps + x) xl) (ps - bst)

main :: IO ()
main = getLine >> getLine >>= print . solve (10^18) 0 . map read . words
