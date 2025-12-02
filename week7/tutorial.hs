firstDigit :: String -> String
firstDigit "" = ""
firstDigit xs = [x | x <- xs, x `elem` [xs!!0]]

exOr :: Bool -> Bool -> Bool
exOr True False = True
exOr False True = True
exOr _ _ = False

exOr2 :: Bool -> Bool -> Bool
exOr2 a b
    | a /= b    = True
    | otherwise = False

elemNum :: Eq a => a -> [a] -> Integer
elemNum _ [] = 0
elemNum x (y:ys)
    | y == x    = 1 + elemNum x ys
    | otherwise = elemNum x ys