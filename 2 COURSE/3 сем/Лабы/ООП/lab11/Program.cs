using System.Collections;
using System.Reflection;
using System.Text;

namespace LW11
{
    public class Prod : IEnumerable, IEnumerator, ICloneable
    {
        public int Id = 0;
        public string Name;

        public Prod()
        {
            this.Id = 1;
        }
        public Prod(int id = 2)
        {
            Id = id;
        }
        public int Method_with_r(int num)
        {
            return Id * num;
        }
        public void Method1()
        {
            PMethod();
        }
        public void Method()
        {
            PMethod();
        }
        public void Method(string str, object obj)
        {
            PMethod();
        }
        private void PMethod()
        {
            Console.WriteLine("Method1");
        }
        public object Current => throw new NotImplementedException();

        public object Clone()
        {
            throw new NotImplementedException();
        }

        public IEnumerator GetEnumerator()
        {
            throw new NotImplementedException();
        }

        public bool MoveNext()
        {
            throw new NotImplementedException();
        }

        public void Reset()
        {
            throw new NotImplementedException();
        }
    }
    public static class Reflector<T>
    {
        public static void Find(T Obj)
        {
            Type myType = Obj.GetType();

            string ReturnString = "";
            ReturnString += "Name: " + myType.Name + "\n";
            ReturnString += "FullName: " + myType.FullName + "\n";
            ReturnString += "Namespace: " + myType.Namespace + "\n";
            ReturnString += "IsValueType: " + myType.IsValueType + "\n";
            ReturnString += "IsClass: " + myType.IsClass + "\n";

            ReturnString += "\n";
            foreach (var i in myType.GetConstructors())
            {
                ReturnString += "Constructors: " + i.Name + "\n";
            }

            ReturnString += "\n";
            foreach (var i in myType.GetMethods())
            {
                ReturnString += "Method: " + i.Name + "\n";
                foreach (var parm in i.GetParameters())
                    ReturnString += "\tParametr: " + parm.ParameterType + "\n";
            }

            ReturnString += "\n";
            foreach (var i in myType.GetFields())
            {
                ReturnString += "Fields: " + i.Name + "\n";
            }

            ReturnString += "\n";

            foreach (var i in myType.GetInterfaces())
            {
                ReturnString += "Interface: " + i.Name + "\n";
            }

            ReturnString += "\n";

            FileStream? fstream = null;
            using (fstream = new FileStream("ClassInfo.txt", FileMode.Create))
            {
                byte[] input = Encoding.Default.GetBytes(ReturnString);
                fstream.Write(input, 0, input.Length);
                fstream.Close();
            }
            Console.WriteLine(ReturnString);
        }

        public static object Create(T obj)
        {
            Type ObjType = obj.GetType();
            return Activator.CreateInstance(ObjType);
        }
    }
    public class Home
    {
        public static void Main()
        {
            Prod first = new Prod();
            Reflector<Prod>.Find(first); 

            Type objType = Type.GetType("LW11.Prod");
            ConstructorInfo objConstr = objType.GetConstructor(Type.EmptyTypes);
            Object ProdObj = objConstr.Invoke(new object[] { });

            Console.WriteLine(ProdObj);
            MethodInfo method = objType.GetMethod("Method_with_r");
            object result = method.Invoke(ProdObj, new object[] { 100 });
            Console.WriteLine(result);


            object result2 = Reflector<Prod>.Create(new Prod());
            Console.WriteLine(result2);
        }
    }
}