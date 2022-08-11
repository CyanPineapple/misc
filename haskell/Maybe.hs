module Test where


(++!) :: [a] -> Int -> Maybe a

(x:xs) ++! 0 = Just x
(x:xs) ++! n = xs ++! (n-1)
[] ++! _ = Nothing
