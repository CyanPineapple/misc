zzip :: [a] -> [b] -> [(a,b)]

zzip [] _ = []

zzip _ [] = []

zzip (sa: xa) (sb: xb) = (sa,sb) : zzip xa xb

-- Abstract zip
zipwith :: (a -> b -> c) -> [a] -> [b] -> [c]

zipwith _ _ [] = []

zipwith _ [] _ = []

zipwith f (s: xs) (t: xt) =  (f s t): zipwith f xs xt


