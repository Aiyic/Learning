#include<bits/stdc++.h>
using namespace std;

class Stock
{
private:
    string str;
public:
    Stock(const string& key):str(key){};
    ~Stock(){;};
    string key(){ return str; }
};

class StockFactory : public std::enable_shared_from_this<StockFactory>{
public:
    shared_ptr<Stock> get(const string& key){
        shared_ptr<Stock> pStock;
        lock_guard<mutex> lock(mutex_);
        weak_ptr<Stock>& wkStock = stocks_[key]; // 注意 wkStock 是引用
        pStock = wkStock.lock();
        if (!pStock){
            auto x = new Stock(key);
            auto y = bind(&StockFactory::weakDeleteCallback, weak_ptr<StockFactory>(shared_from_this()), placeholders::_1);
            pStock.reset(x, y);
            // 上面必须强制把 shared_from_this() 转型为 weak_ptr，才不会延长生命期，
            // 因为 boost::bind 拷贝的是实参类型，不是形参类型
            wkStock = pStock;
        }
        return pStock;
    }
private:
    static void weakDeleteCallback(const weak_ptr<StockFactory>& wkFactory, Stock* stock) {
        shared_ptr<StockFactory> factory(wkFactory.lock()); // 尝试提升
        if (factory){ // 如果 factory 还在，那就清理 stocks_
            factory->removeStock(stock);
        }
        delete stock; // sorry, I lied
    }
    void removeStock(Stock* stock){
        if (stock){
            lock_guard<mutex> lock(mutex_);
            stocks_.erase(stock->key());
        }
    }
private:
    mutable mutex mutex_;
    std::map<string, weak_ptr<Stock> > stocks_;
};


void testLongLifeFactory(){
    shared_ptr<StockFactory> factory(new StockFactory);
    {
        shared_ptr<Stock> stock = factory->get("NYSE:IBM");
        shared_ptr<Stock> stock2 = factory->get("NYSE:IBM");
        assert(stock == stock2);
        // stock destructs here
    }
    // factory destructs here
}
void testShortLifeFactory(){
    shared_ptr<Stock> stock;
    {
        shared_ptr<StockFactory> factory(new StockFactory);
        stock = factory->get("NYSE:IBM");
        shared_ptr<Stock> stock2 = factory->get("NYSE:IBM");
        assert(stock == stock2);
        // factory destructs here
    }
    // stock destructs here
}

int main(){
    testLongLifeFactory();
    testShortLifeFactory();
    return 0;
}