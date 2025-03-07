#ifndef FILE_MESSAGE_BROKER_HPP
#define FILE_MESSAGE_BROKER_HPP

#include <fstream>

#include "messageBroker/messageBroker.hpp"

namespace lab7 {
    class FileMessageBroker : public MessageBroker<std::mutex> {
    public:
        using super = MessageBroker<std::mutex>;
        using mutex_type_ptr = super::mutex_type_ptr;
        
        FileMessageBroker(const std::string& filename, mutex_type_ptr mutex_ptr) 
            : super(mutex_ptr),
              filename(filename) {
            try {
                fout.open(filename, std::ofstream::out | std::ofstream::app);
                is_open_stream = true;
            } catch (const std::ios_base::failure& e) {
                throw std::runtime_error("Error: can not open file " + filename + "\n");
            }
        }

        FileMessageBroker(const FileMessageBroker& other) 
            : FileMessageBroker(other.filename, other.mutex_ptr) {}

        FileMessageBroker(FileMessageBroker&& other) 
            : super(std::move(other.mutex_ptr)),
              fout(std::move(other.fout)), 
              filename(std::move(other.filename)),
              is_open_stream(fout.is_open()) {}

        FileMessageBroker& operator=(FileMessageBroker&& other) {
            fout = std::move(other.fout);
            filename = std::move(other.filename);
            is_open_stream = fout.is_open();
            return *this;
        }

        ~FileMessageBroker() {
            if (is_open_stream) {
                close();
            }
        }  

        void unsafeSendMessage(const std::string& message) {
            if (!is_open_stream) {
                throw std::runtime_error("Error: trying to write message to closed filestream!\n");
            } else {
                fout << message;
            }
        }

        void close() {
            try {
                fout.close();
                is_open_stream = false;
            } catch (const std::ios_base::failure& e) {
                throw std::runtime_error("Error: trying to close not open file\n");
            }
        }

        bool is_open_file() {
            return is_open_stream;
        }

    protected:
        bool is_open_stream;
        std::ofstream fout;
        std::string filename;
    };
};

#endif