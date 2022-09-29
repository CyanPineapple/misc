data Mayb a = Jus {label::a} | Nothin

addOne :: Mayb Int -> Mayb Int

addOne (Jus a) = Jus (a + 1)
addOne Nothin = Nothin


instance Functor ((,)a) where
    fmap f (x,y) = (x, f y)

