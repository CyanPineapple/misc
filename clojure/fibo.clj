(defn fibo [iter] (let [fibo_recur(fn [one two n]
                   (if (= n iter)
                      two
                      (recur two (+ one two) (inc n))))]
                   (fibo_recur 1 2 3)))

(time (fibo 50))


(def fibo-m 
  ( memoize (fn [iter] (let [fibo_recur(fn [one two n]
                   (if (= n iter)
                      two
                      (recur two (+ one two) (inc n))))]
                   (fibo_recur 1 2 3)))))

(time (fibo-m 50))
