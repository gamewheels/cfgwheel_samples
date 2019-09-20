using System;
public class Singleton<T> where T : class
{
    private static T _instance;
    public static T Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = (T)Activator.CreateInstance(typeof(T), true);
            }
            return _instance;
        }
    }
}
