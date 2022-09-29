newtype Pair b a = Pair {getPair :: (b,a)}
instance Functor (Pair c) where
    fmap f (Pair (x,y)) = Pair (x, f y)
