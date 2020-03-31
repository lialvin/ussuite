
#ifndef DAPPCLI_TIME_SAVE_HPP
#define DAPPCLI_TIME_SAVE_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>
 
#include <iostream>
#include <fstream>

class timeDeal {
public:
    timeDeal(boost::asio::io_context& io,std::string file) :strand_(io),
    save_file(file),
    timer1_(io,boost::asio::chrono::seconds(1)),
	timer2_(io,boost::asio::chrono::seconds(1)),
	count_(0)
	{
        timer1_.async_wait(boost::asio::bind_executor(strand_,boost::bind(&timeDeal::onSave1,this)));
        timer2_.async_wait(boost::asio::bind_executor(strand_,boost::bind(&timeDeal::onSave2,this)));
    }

    ~timeDeal() {
        std::cout << "Final count is " << count_ << std::endl;
    }

    void onSave1() {
        
        //std::cout << "Timer 1: " << count_ << std::endl;
        ++count_;
		saveData();	
		timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(5));
		timer1_.async_wait(boost::asio::bind_executor(strand_,boost::bind(&timeDeal::onSave1,this)));        
    }

    void onSave2() {
        if (count_ < 10) {
            std::cout << "Timer 2: " << count_ << std::endl;
            ++count_;
            timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(6));
            timer2_.async_wait(boost::asio::bind_executor(strand_,boost::bind(&timeDeal::onSave2,this)));
        }
    }
	
	void updateData(std::string  hostdata)
	{
		int pos = hostdata.find("\n");
		std::string keystr = hostdata.substr(0,pos);
		uosdata[keystr] = hostdata;
	}
	
private:

	//save disk data
	void  saveData()
	{		
	
	}
    std::string save_file;	
	std::map<std::string,std::string> uosdata;
	
    boost::asio::steady_timer timer1_;
    boost::asio::steady_timer timer2_;
    int count_;
    boost::asio::io_context::strand strand_;
};
 
timeDeal  * g_timeDeal;

#endif //DAPPCLI_TIME_SAVE_HPP

