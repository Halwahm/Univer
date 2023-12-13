using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Server;
using System.IO;

[Serializable]
[SqlUserDefinedType(Format.UserDefined, MaxByteSize = 8000, IsByteOrdered = true)]
public struct CustomType : INullable, IBinarySerialize
{
    private string _test;
    private bool _isNull;

    public override string ToString()
    {
        return _isNull ? "NULL" : _test;
    }

    public bool IsNull => _isNull;

    public static CustomType Null => new CustomType { _isNull = true };

    public void Read(BinaryReader r)
    {
        if (r != null)
        {
            _test = r.ReadString();
            _isNull = _test == null;
        }
    }

    public void Write(BinaryWriter w)
    {
        if (w != null)
        {
            w.Write(_test);
        }
    }

    public static CustomType Parse(SqlString s)
    {
        if (s.IsNull)
        {
            return Null;
        }

        string input = s.Value;
        if (input == "success")
        {
            return new CustomType { _test = input, _isNull = false };
        }
        else
        {
            throw new ArgumentException("Input value can only be 'success'");
        }
    }
}
