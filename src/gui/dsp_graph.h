#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <imgui.h>
#include <imnodes.h>

// 節點類型
enum class DSPNodeType {
    Synthesizer,
    Filter,
    Effect,
    Mixer,
    Output
};

// 節點結構
struct DSPNode {
    int id;
    DSPNodeType type;
    std::string name;
    std::vector<int> inputs; // 連接的輸入節點
    std::vector<int> outputs; // 連接的輸出節點
    float param1; // 參數1 (如頻率, 增益)
    float param2; // 參數2 (如 Q 值, reverb time)
};

class DSPGraph {
public:
    DSPGraph();
    void render();
    int addNode(DSPNodeType type, const std::string& name);
    void addLink(int from, int to);

private:
    int nextNodeId;
    std::unordered_map<int, DSPNode> nodes;
    std::vector<std::pair<int, int>> links; // 連接關係
};

