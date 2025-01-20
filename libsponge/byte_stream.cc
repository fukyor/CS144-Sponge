#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity)   
    : buffer_()
    , bytes_pushed_(0)
    , bytes_popped_(0)
    , closed_(false)
    , capacity_(capacity)
    , _error(false){}

size_t ByteStream::write(const string &data) {
    string tmp;
     /*计算当前可用容量*/
    size_t cur_capacity = remaining_capacity();
    size_t write_size = min(data.size(), cur_capacity);
    /*如果数据长度大于可用容量，则只写入可用容量*/
    tmp = data.substr( 0, write_size );
    /*将数据写入缓冲区*/
    buffer_.insert( buffer_.end(), tmp.begin(), tmp.end() ); // 用迭代器代替队尾指针
    /*更新已写入的字节数*/
    bytes_pushed_ += write_size;
    return write_size;
}

//! \param[in] len bytes will be copied from the output side of the buffer
//如果buffer_为空返回空string，否则返回buffer_的前len个元素;
string ByteStream::peek_output(const size_t len) const {
    return buffer_.empty()
           ? string()
           : string(buffer_.begin(), buffer_.begin() + len);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    // 从buffer_前端移除len个字节，更新bytes_popped_
    bytes_popped_ += len;
    buffer_.erase( buffer_.begin(), buffer_.begin() + len ); // 用迭代器代替队首指
 }

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string tmp = peek_output(len);
    pop_output(len);
    return tmp;
}

void ByteStream::end_input() { closed_ = true; }// `true` if the stream input has ended

bool ByteStream::input_ended() const {  return closed_; }// `true` if the stream input has ended

size_t ByteStream::buffer_size() const { return buffer_.size(); } //the maximum amount that can currently be peeked/read

bool ByteStream::buffer_empty() const { return buffer_.empty(); }

bool ByteStream::eof() const { return closed_ && buffer_empty(); } // `true` if the stream input has ended and the buffer is empty

size_t ByteStream::bytes_written() const { return bytes_pushed_; }

size_t ByteStream::bytes_read() const { return bytes_popped_; }

size_t ByteStream::remaining_capacity() const { return capacity_ - buffer_.size();  }// 返回当前可用容量;
