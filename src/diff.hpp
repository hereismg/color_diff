#ifndef DIFF_HPP
#define DIFF_HPP

#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>

namespace mg{
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
            res.push_back(line + "\n");
        }
    
        return res;
    }
    
    int dx[] = {0, -1, -1};
    int dy[] = {-1, -1, 0};
    
    enum class Stats{
        DELETE,
        ADDITION,
        SAME
    };
    
    class Text{
    public:
        std::vector<std::string> m_befor;
        std::vector<std::string> m_after;
        std::vector<std::pair<Stats, std::string>> m_diff;
        Text(const std::string& befor, const std::string& after):m_befor(split(befor, '\n')), m_after(split(after, '\n')){}
        Text(std::vector<std::string> befor, std::vector<std::string> after): m_befor(befor), m_after(after){}
    
        int diff(){
            std::vector<std::vector<int>> dp(m_befor.size()+1, std::vector<int>(m_after.size()+1, 0)),
                                parent(m_befor.size()+1, std::vector<int>(m_after.size()+1, -1));
    
            // dp 求出结果
            for (int i=1; i<=m_befor.size(); i++){
                for (int j=1; j<=m_after.size(); j++){
                    if (m_befor[i-1].compare(m_after[j-1]) == 0){
                        dp[i][j] = dp[i-1][j-1] + 1;
                        parent[i][j] = 1; // 斜角
                    }
                    else{
                        dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
    
                        if (dp[i-1][j]>dp[i][j-1]) parent[i][j] = 2;
                        else parent[i][j] = 0;
                    }
                }
            }
    
            // 求出具体的相同点
            int x=m_befor.size(), y=m_after.size();
    
            while(parent[x][y] != -1){
                int cur = parent[x][y];
                if (cur == 1){
                    m_diff.emplace_back(Stats::SAME, m_befor[x-1]);
                }
                else if (cur == 0){
                    m_diff.emplace_back(Stats::ADDITION, m_after[y-1]);
                }
                else if (cur == 2){
                    m_diff.emplace_back(Stats::DELETE, m_befor[x-1]);
                }
                else{
                    assert(false);
                }
                x += dx[cur];
                y += dy[cur];
            }
    
            std::reverse(m_diff.begin(), m_diff.end());
    
            return dp[m_befor.size()][m_after.size()];        
        }
    };
    
}

#endif