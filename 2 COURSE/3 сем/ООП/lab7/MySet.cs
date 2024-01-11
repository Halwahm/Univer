namespace lab7
{
    public class DAt { }
    public class MySet<T> : IGeneric<T> where T : class
    {
        public HashSet<T> _set;
        private const int MaxLen = 5;

        public MySet(T value)
        {
            _set = new HashSet<T> { value };
        }

        public T this[int index]
        {
            get
            {
                if (index > (int)this - 1 || index < 0)
                    throw new ArgumentOutOfRangeException();

                var size = 0;
                foreach (var item in _set)
                {
                    if (size == index)
                        return item;
                    size++;
                }

                return default(T);
            }
            set
            {
                if (index > (int)this - 1 || index < 0)
                    throw new ArgumentOutOfRangeException();

                //var set = new HashSet<T>();
                var size = 0;

                foreach (var item in _set)
                {
                    _set.Add(size == index ? value : item);
                    size++;
                }
                //_set = set;
            }
        }

        #region operators
        public static MySet<T> operator +(MySet<T> set, T item)
        {
            set._set.Add(item);
            return set;
        }

        public static MySet<T> operator +(MySet<T> set, MySet<T> set2)
        {
            foreach (var e in set2._set)
            {
                set += e;
            }

            return set;
        }

        public static MySet<T> operator *(MySet<T> set, MySet<T> set2)
        {
            set._set.IntersectWith(set2._set);
            return set;
        }

        public static explicit operator int(MySet<T> set)
        {
            return set._set.Count;
        }


        public static bool operator false(MySet<T> set)
        {
            return (int)set > MaxLen;
        }

        public static bool operator true(MySet<T> set)
        {
            return (int)set <= MaxLen;
        }
        #endregion

        public void Add(T dt)
        {
            _set.Add(dt);
        }

        public void Delete(T dt)
        {
            _set.Remove(dt);
        }

        public void Show()
        {
            foreach (var str in _set)
            {
                Console.WriteLine($"value: {str}\n");
            }
        }

        public static void WriteToFile(MySet<T> set)
        {
            using (var file = new StreamWriter("file.txt", false))
            {
                foreach (var item in set._set)
                {
                    file.Write($"{item}\n");
                }
            }
        }

        public static void ReadFromFile()
        {
            using (var file = new StreamReader("file.txt", true))
            {
                Console.WriteLine(file.ReadToEnd());
            }
        }
    }
}
