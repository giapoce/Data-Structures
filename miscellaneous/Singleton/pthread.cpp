class Mutex
{
  public:
    Mutex()
    { pthread_mutex_init(&m, 0); }
 
    void lock()
    { pthread_mutex_lock(&m); }
 
    void unlock()
    { pthread_mutex_unlock(&m); }
 
  private:
    pthread_mutex_t m;
};
 
class MutexLocker
{
  public:
    MutexLocker(Mutex& pm): m(pm) { m.lock(); }
    ~MutexLocker() { m.unlock(); }
  private:
    Mutex& m;
};
 
class Singleton
{
  public:
    static Singleton& Instance();
    int example_data;
    ~Singleton() { }
 
  protected:
    Singleton(): example_data(42) { }
 
  private:
    static std::auto_ptr<Singleton> theSingleInstance;
    static Mutex m;
};
 
Singleton& Singleton::Instance()
{
    if (theSingleInstance.get() == 0)
    {
      MutexLocker obtain_lock(m);
      if (theSingleInstance.get() == 0)
      {
        theSingleInstance.reset(new Singleton);
      }
    }
    return *theSingleInstance;
}
 
std::auto_ptr<Singleton> Singleton::theSingleInstance;
Mutex Singleton::m;
 
int main()
{
    std::cout << Singleton::Instance().example_data << std::endl;
    return 0;
}
