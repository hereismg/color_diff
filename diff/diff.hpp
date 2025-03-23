#ifndef DIFF_HPP
#define DIFF_HPP

#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>

namespace mg{
    // ======================= 颜色控制代码 =======================
    namespace Color {
        // 格式重置
        static const std::string RESET = "\033[0m";
        
        // 常规前景色
        static const std::string BLACK  = "\033[30m";
        static const std::string RED    = "\033[31m";
        static const std::string GREEN  = "\033[32m";
        static const std::string YELLOW = "\033[33m";
        static const std::string BLUE   = "\033[34m";
        static const std::string PURPLE = "\033[35m";
        static const std::string CYAN   = "\033[36m";
        static const std::string WHITE  = "\033[37m";
    
        // 加粗前景色
        static const std::string BOLD_BLACK  = "\033[1;30m";
        static const std::string BOLD_RED    = "\033[1;31m";
        static const std::string BOLD_GREEN  = "\033[1;32m";
        static const std::string BOLD_YELLOW = "\033[1;33m";
        static const std::string BOLD_BLUE   = "\033[1;34m";
        static const std::string BOLD_PURPLE = "\033[1;35m";
        static const std::string BOLD_CYAN   = "\033[1;36m";
        static const std::string BOLD_WHITE  = "\033[1;37m";
    
        // 背景色
        static const std::string BG_BLACK  = "\033[40m";
        static const std::string BG_RED    = "\033[41m";
        static const std::string BG_GREEN  = "\033[42m";
        static const std::string BG_YELLOW = "\033[43m";
        static const std::string BG_BLUE   = "\033[44m";
        static const std::string BG_PURPLE = "\033[45m";
        static const std::string BG_CYAN   = "\033[46m";
        static const std::string BG_WHITE  = "\033[47m";
    }
    
    // ======================= 彩色输出流类 =======================
    class ColorOstream {
    public:
        // 构造函数：绑定到指定的输出流（默认使用 std::cout）
        explicit ColorOstream(std::ostream& os = std::cout) : os_(os) {}
    
        // 重载 << 操作符，支持链式调用
        template<typename T>
        ColorOstream& operator<<(const T& val) {
            os_ << val;
            return *this;
        }
    
        // 重载 << 操作符，专门处理颜色代码（自动重置）
        ColorOstream& operator<<(const std::string& color_code) {
            if (color_code == Color::RESET) {
                os_ << Color::RESET;
            } else {
                os_ << color_code;
            }
            return *this;
        }
    
        // 兼容 std::endl 等流操作符
        typedef std::ostream& (*StreamManip)(std::ostream&);
        ColorOstream& operator<<(StreamManip manip) {
            manip(os_);
            return *this;
        }
    
    private:
        std::ostream& os_;  // 底层输出流
    };
    
    // ======================= 全局实例化 =======================
    ColorOstream color_cout;  // 默认使用 std::cout


    std::vector<std::string> split(const std::string& str, char c){
        int l=0;
        std::vector<std::string> arrStr;
    
        while (l < str.size()){
            int r = l;
            while(r<str.size() && str[r]!=c) r++;
            arrStr.push_back(str.substr(l, r-l+1));
            l = r+1;
        }
    
        return std::move(arrStr);
    }
    
    std::vector<std::string> read(const std::string& path){
        std::ifstream after_file(path);
        assert(after_file.is_open());
    
        
        std::vector<std::string> res;
        std::string line;
        while(getline(after_file, line)){
            res.push_back(line + "\n"); // 注意，这里默认添加了换行符！
        }
    
        return res;
    }
    
    int dx[] = {0, -1, -1};
    int dy[] = {-1, -1, 0};
    
    enum class State{
        DELETE,
        ADDITION,
        SAME
    };
    
    class Text{
    private:
        std::vector<std::string> m_befor;
        std::vector<std::string> m_after;
        std::vector<std::pair<State, std::string>> m_diff;

        std::vector<std::vector<int>> m_dp;
        std::vector<std::vector<int>> m_parent;

    public:
        Text(const std::string& befor, const std::string& after):
            m_befor (split(befor, '\n')), 
            m_after (split(after, '\n')),
            m_dp    (m_befor.size()+1, std::vector<int>(m_after.size()+1, 0)),
            m_parent(m_befor.size()+1, std::vector<int>(m_after.size()+1, -1))
            {}
        Text(std::vector<std::string> befor, std::vector<std::string> after): 
            m_befor (befor), 
            m_after (after),
            m_dp    (m_befor.size()+1, std::vector<int>(m_after.size()+1, 0)),
            m_parent(m_befor.size()+1, std::vector<int>(m_after.size()+1, -1))
            {}
    

    public:
        int calc_dp(){
            for (int i=1; i<=m_befor.size(); i++){
                for (int j=1; j<=m_after.size(); j++){
                    if (m_befor[i-1].compare(m_after[j-1]) == 0){
                        m_dp[i][j] = m_dp[i-1][j-1] + 1;
                        m_parent[i][j] = 1; // 斜角
                    }
                    else{
                        m_dp[i][j] = std::max(m_dp[i-1][j], m_dp[i][j-1]);
    
                        if (m_dp[i-1][j]>m_dp[i][j-1]) m_parent[i][j] = 2;
                        else m_parent[i][j] = 0;
                    }
                }
            }
            return m_dp[m_befor.size()][m_after.size()];
        }
        
        // ========== 求出文本差异 =========
        void calc_diff(){
            calc_dp();
    
            // 求出具体的相同点
            int x=m_befor.size(), y=m_after.size();
    
            while(m_parent[x][y] != -1){
                int cur = m_parent[x][y];
                if (cur == 1){
                    m_diff.emplace_back(State::SAME, m_befor[x-1]);
                }
                else if (cur == 0){
                    m_diff.emplace_back(State::ADDITION, m_after[y-1]);
                }
                else if (cur == 2){
                    m_diff.emplace_back(State::DELETE, m_befor[x-1]);
                }
                else{
                    assert(false);
                }
                x += dx[cur];
                y += dy[cur];
            }
    
            std::reverse(m_diff.begin(), m_diff.end());
        }

        void showDiff(){
            calc_diff();

            for (auto iter: m_diff){
                if (iter.first == State::SAME){
                    color_cout << "  │ " << iter.second;
                }
                else if (iter.first == State::ADDITION){
                    color_cout << Color::GREEN << "+ │ " << iter.second << Color::RESET;
                }
                else if (iter.first == State::DELETE){
                    color_cout << Color::RED << "- │ " << iter.second << Color::RESET;
                }
            }
        }
    };
    
}

#endif