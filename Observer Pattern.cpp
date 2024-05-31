#include<iostream>
#include<array>
#include<vector>
#include <fstream>

class Observer
{
public:
    virtual void onWarning(const std::string& message) {
    }

    virtual void onError(const std::string& message) {
    }

    virtual void onFatalError(const std::string& message) {
    }

};


class Errors
{
private:
    std::string message;
    std::vector<Observer*> observers;
    Observer* observer;

public:

    void warning(const std::string& message) const {
        for (Observer* observer : observers)
        {
            observer->onWarning(message);
        }
    }

    void error(const std::string& message) const {
        for (Observer* observer : observers)
        {
            observer->onError(message);
        }
    }

    void fatalError(const std::string& message) const {
        for (Observer* observer : observers)
        {
            observer->onFatalError(message);
        }
    }



    void registerObserver(Observer* observer)
    {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer)
    {
        auto it = remove(observers.begin(), observers.end(), observer);
        observers.erase(it, observers.end());
    }

    void notifyObservers()
    {
        for (Observer* observer : observers)
        {
            observer->onError(message);
        }
    }

    void setMeasurements(const std::string& message_)
    {
        message = message_;
        notifyObservers();
    }

};


class print_on_console : public Observer {
public:
    void onWarning(const std::string& message) {
        std::cout << "This message: "<< message << " is warning\n";

    }
};


class print_on_file : public Observer {
public:
    std::ofstream out;
    print_on_file() {
        out.open("file");


    }

    void onError(const std::string& message) {
        if (out.is_open())
        {
            out << "This message: " << message << " is error\n";
        }
    }
};

class print_on_file_and_console : public Observer {
public:
    std::ofstream out;
    print_on_file_and_console() {
        out.open("file");


    }
    void onFatalError(const std::string& message) {
        if (out.is_open())
        {
            out << "This message: " << message << " is fatal error\n";
        }
        std::cout << "This message: " << message << " is fatal error\n";
    }
        
    
};

int main()
{
    Errors error;

    print_on_console war;
    print_on_file err;
    print_on_file_and_console fat_err;

    error.registerObserver(&war);
    error.warning("console");

    error.registerObserver(&err);
    error.error("file");

    error.registerObserver(&fat_err);
    error.fatalError("console and file ");
    
    return 0;
}