#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    // 1. 处理 EOF
    if (eof) {
        _eof = true;
        _eof_idx = index + data.size(); // 记录结束位置为最后一个字符的下一个位置
    }
    // 2. 处理重叠数据
    /* 说明输入数据流和之前的数据流有重叠*/
    /*1. 当前数据流是之前已经整流完毕的数据流，直接返回*/
    /*2. 当前数据流是之前未整流完毕的数据流，需要整流*/
    if(index <= _next_assembled_idx) { 
        if(index + data.size() < _next_assembled_idx) { //当前数据流是之前已经整流完毕的数据流，直接返回
            return; 
        }
        /* 当前数据流是之前未整流完毕的数据流，需要整流*/
        if (index + data.size() > _next_assembled_idx) {
            string unassembled = data.substr(_next_assembled_idx - index); // 处理部分重叠：取出未重叠部分,并直接写入ByteStream即可
            auto write_count = _output.write(unassembled);
            _next_assembled_idx += write_count;

            auto iter = _memo.begin();
            while (iter != _memo.end() && iter->first <= _next_assembled_idx) { // 等于也可以，因为等于的时候刚好是第一个未被整流的数据，我们直接对它进行整流即可。必须要iter->first <= _next_assembled_idx时才可以被整流并输出到ByteStream
                auto sz = iter->second.size();
                if (iter->first + sz >= _next_assembled_idx) {
                // 整流之前在assembler中未整流的数据，并写入ByteStream
                auto existed_str = iter->second.substr(_next_assembled_idx - iter->first);
                auto add_count = _output.write(existed_str);
                _next_assembled_idx += add_count;
                }
                _unassembled_bytes -= sz;
                iter = _memo.erase(iter);
            }
        }
    }
    else{
        string s = data;
        size_t idx = index;
        auto iter = _memo.lower_bound(idx); // 找到第一个大于等于index的元素
        // 后向合并第一个大于等于index的元素
        while (iter != _memo.end() && iter->first <= idx + s.size()) {
            auto sz = iter->second.size();
            if (iter->first + sz > idx + s.size()) {
                s += iter->second.substr(idx + s.size() - iter->first); // 合并
            }
            _unassembled_bytes -= sz;
            iter = _memo.erase(iter);
        }
        // 前向合并
        iter = _memo.lower_bound(idx);
        if (iter != _memo.begin() && !_memo.empty()) {
            iter--;  // 找到小于idx的第一个元素
            auto sz = iter->second.size();
            if (iter->first + sz >= idx) { 
                if (iter->first + sz > idx + s.size()) { // 如果合并数据长度大于idx+s.size()，则直接用iter->second替换s，因为此时iter->second包含了s
                    s = iter->second;
                } 
                else { // 如果合并数据长度小于idx+s.size()，则将iter->second和s合并
                    s = iter->second + s.substr(iter->first + sz - idx);
                }
                _unassembled_bytes -= sz;
                idx = iter->first; // 更新新的起始位置
                _memo.erase(iter);
            }
        }
        auto store_count = std::min(s.size(), _capacity - _output.buffer_size() - _unassembled_bytes); // 因为_capacity由两部分组成，一部分在ByteStream中表示已经重组完毕,一部分在assembler中表示还未重组，他们共同占用接受窗口的大小_capacity。所以我们需要确定新重组的数据和接受窗口的剩余大小哪个大，选小的
        _unassembled_bytes += store_count;
        _memo.emplace(idx, s.substr(0, store_count));
    }
    // 检查是否到达 EOF
    if (_eof && _next_assembled_idx >= _eof_idx) {
        _output.end_input();
    }
}

size_t StreamReassembler::unassembled_bytes() const { return _unassembled_bytes; }

bool StreamReassembler::empty() const { return unassembled_bytes() == 0; }
