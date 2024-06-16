import qualified Data.Map as Map

solve :: Map.Map Int Int -> Int -> Int -> [Int] -> Int
solve occ sum n [] = Map.findWithDefault 0 sum occ
solve occ sum n (v : vs) = (Map.findWithDefault 0 sum occ) + (solve (Map.insert sum ((Map.findWithDefault 0 sum occ) + 1) occ) ((sum + v) `mod` n) n vs)

main :: IO ()
main = getLine >>= (\n -> getLine >>= print . solve Map.empty 0 n . map read . words) . read
