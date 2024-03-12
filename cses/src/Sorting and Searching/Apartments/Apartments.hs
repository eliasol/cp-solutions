import Data.List ( sort )

solve :: Int -> [Int] -> [Int] -> Int
solve _ [] _ = 0
solve _ _ [] = 0
solve k (a : ar) (b : br)
    | a < b - k = solve k ar (b : br)
    | a > b + k = solve k (a : ar) br
    | otherwise = 1 + solve k ar br

main :: IO ()
main = do
    firstLine <- getLine
    let firstLineSplitted = map (read :: String -> Int) $ words firstLine
    aRaw <- getLine
    bRaw <- getLine
    let a = sort $ map read $ words aRaw
    let b = sort $ map read $ words bRaw
    print $ solve (firstLineSplitted !! 2) a b
