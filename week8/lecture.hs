type String = [Char]
type Pos = (Int, Int)
origin :: Pos
origin = (0, 0)

left :: Pos -> Pos
left (x, y) = (x-1, y)

type Pair a = (a, a) -- a is a type
mult :: Pair Int -> Int
mult (m, n) = m * n

copy :: a -> Pair a
copy x = (x, x)

data Bool = False | True
data Answer = Yes | No | Unknown
--answers :: [Answer]
--answers :: [Yes, No, Unknown]

flip :: Answer -> Answer
flip Yes = No
flip No = Yes
flip Unknown = Unknown

data Shape = Circle Float | Rect Float Float -- Circle :: Float -> Shape | Rect :: Float -> Float -> Shape
square :: Float -> Shape
square n = Rect n n

area :: Shape -> Float
area (Circle r) = pi * r^2
area (Rect x y) = x * y

--data Maybe a = Nothing | Just a
safeDiv :: Int -> Int -> Maybe Int
safeDiv _ 0 = Nothing
safeDiv m n = Just(m `div` n)

safeHead :: [a] -> Maybe a
safeHead [] = Nothing
safeHead xs = Just(head xs)

data Nat = Zero | Succ Nat
nat2int :: Nat -> Int
nat2int Zero = 0
nat2int (Succ n) = 1 + nat2int n

int2nat :: Int -> Nat
int2nat 0 = Zero
int2nat n = Succ (int2nat (n-1))

add :: Nat -> Nat -> Nat
-- converting to integer
add m n = int2nat (nat2int m + nat2int n)

-- by recursion without conversion
-- add Zero n = n
-- add (Succ m) n = Succ (add m n)


