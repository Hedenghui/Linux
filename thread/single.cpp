#include <cstdio>

/*
class single_instance
{
    public:
        int * get_instance(){
            return &_data;
        }
    private:
        static int _data;
};
int single_instance::_data = 10;//静态成员变量需要在类外初始化
*/

#include <thread>
#include <mutex>
std::mutex g_mutex;
class single_instance
{
    public:
        volatile int *get_instance() {
            //不管——data资源是否已经被加载，每次都要加锁判断，然后解锁
            //若资源已经加载过了，加锁解锁就有点浪费资源，并且容易造成锁冲突
            //4. 二次判断，避免每次都会加锁解锁
            if (_data == NULL) {
                //-----------------//
                g_mutex.lock();//3. 实现线程安全
                if (_data == NULL) {
                    _data = new int;
                    *_data = 10;
                }
                g_mutex.unlock();
            }
            return _data;
        }
    private:
        //1. static 保证所有对象使用同一份资源
        //2. volatile 防止编译器过度优化
        volatile static int *_data;
};
volatile int *single_instance::_data = NULL;

int main()
{
    single_instance a1;
    single_instance b1;

    printf("a1:%d-%p\n", *(a1.get_instance()), a1.get_instance()); 
    printf("b1:%d-%p\n", *(b1.get_instance()), b1.get_instance()); 
}
