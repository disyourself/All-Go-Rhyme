
// 封装，继承，多态
// 但是多态有点多余， 不好控制，并且需要经过两次跳转
// 预取指令失效

#include <functional>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

using std::cout, std::cin, std::endl;


struct Hero
{
    Hero() { cout << "Hero()" << endl; }
    /* virtual void show()
    {
        cout << " 英雄释放了技能" << endl;
    }*/

    /*****************************************/
    // 用 function 和 bind 替代多态
    std::function<void()> m_callback;

    template <typename Fn, typename... Args>
    void bind_cb(Fn &&fn, Args &&...args)
    {
        m_callback = std::bind(std::forward<Fn>(fn),
                               std::forward<Args>(args)...);
    }

    void show() { m_callback(); }
    /*****************************************/

    virtual ~Hero() { cout << "~Hero" << endl; }
};


struct HX : public Hero
{
    HX() { cout << "HX construct" << endl; }
    void show() /*override*/
    {
        cout << "韩信 释放了技能" << endl;
    }
    ~HX() { cout << "HX destruct" << endl; }
};
struct LB : public Hero
{
    LB() { cout << "LB construct" << endl; }
    void show() /*override*/
    {
        cout << "李白 释放了技能" << endl;
    }
    ~LB() { cout << "LB destruct" << endl; }
};

int main()
{
    cout << "选择: 1-HX, 2-LB" << endl;
    int id;
    cin >> id;

    std::unique_ptr<Hero> hero;

    switch (id) {
    case 1:
        hero = std::make_unique<HX>();
        // 绑定 hero 内的 m_callback 为子类的函数
		// 两个类之间不需要有继承关系
		// 但为了便捷绑定，尽量少构造固定的对象
		// 采用了 继承关系 和 指针转换
        hero->bind_cb(&HX::show, dynamic_cast<HX *>(hero.get()));
        break;
    case 2:
        hero = std::move(std::make_unique<HX>());
        hero->bind_cb(&LB::show, dynamic_cast<LB *>(&*hero));
        break;
    default:
        cout << "输入错误!" << endl;
        return -1;
    }

    hero->show();

    // 如何由父类u_ptr 调用子类析构
    // ans: 需要将父类的析构设置为virtual fun
	// 而采用 bind 和 function 就不需要

    return 0;
}
