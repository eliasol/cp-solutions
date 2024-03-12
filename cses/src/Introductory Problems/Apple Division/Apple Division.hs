solve :: Int -> Int -> [Int] -> Int
solve a b [] = abs(a - b)
solve a b (l : lr) = min (solve (a + l) b lr) (solve a (b + l) lr)

main :: IO ()
main = getLine >> getLine >>= (print . solve 0 0 . map read . words)
