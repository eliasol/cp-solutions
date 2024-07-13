solve :: [Int] -> Int
solve v
    | m <= s - m = s
    | otherwise = 2 * m
      where m = maximum v
            s = sum v

main :: IO ()
main = getLine >> getLine >>= print . solve . map read . words
