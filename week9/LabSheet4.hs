squareList :: [Int] -> [Int]
squareList ns = [x*x | x <- ns]

sumSquareList :: [Int] -> Int
sumSquareList [] = 0
sumSquareList ns = (head ns * head ns) + sumSquareList (tail ns)

posList :: [Int] -> Bool
posList [] = True
posList ns = all (>0) ns
-- posList ns = (head ns > 0) && posList (tail ns)

minValue :: (Int -> Int) -> Int -> Int
minValue f n = minimum (map f [0..n])

equalValue :: (Int -> Int) -> Int -> Bool
equalValue f n = all (== head (map f [0..n])) (map f [0..n])

posValue :: (Int -> Int) -> Int -> Bool
posValue f n = all (>0) (map f [0..n])

incValue :: (Int -> Int) -> Int -> Bool
incValue f 0 = True
incValue f n = f n >= f (n-1) && incValue f (n-1)

twice :: (Int -> Int) -> Int -> Int
twice f x = (f . f) x

iter :: Int -> (Int -> Int) -> Int -> Int
iter 0 f x = x
iter n f x = f (iter (n-1) f x)

double :: Int -> Int
double x = x * 2

powerBin :: Int -> Int
powerBin 0 = 1
powerBin n = double (powerBin (n-1))

data RhType = Positive | Negative
data ABOType = A | B | AB | O
data BloodType = Rh RhType | ABO ABOType

showRh :: RhType -> String
showRh Positive = "Positive"
showRh Negative = "Negative"

showABO :: ABOType -> String
showABO A = "A"
showABO B = "B"
showABO AB = "AB"
showABO O = "O"

showBloodType :: BloodType -> String
showBloodType (Rh rh) = showRh rh
showBloodType (ABO abo) = showABO abo

canDonateTo :: BloodType -> [String]
canDonateTo x
    | showBloodType x == "A" = ["A", "AB"]
    | showBloodType x == "B" = ["B", "AB"]
    | showBloodType x == "AB" = ["AB"]
    | showBloodType x == "O" = ["A", "B", "AB"]

data Answer = Yes | No | Unknown
wonky :: Answer -> Answer
wonky Yes = No
wonky No = Unknown
wonky Unknown = Yes

-- data Shape = Circle Float | Rect Float Float
data Shape = Ellipse Float Float | Rect Float Float
square :: Float -> Shape
square n = Rect n n

area :: Shape -> Float
-- area (Circle r) = pi * r^2
area (Ellipse x y) = pi * x * y
area (Rect x y) = x * y
