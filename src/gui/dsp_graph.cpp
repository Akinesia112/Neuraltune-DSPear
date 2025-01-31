#include "gui/dsp_graph.h"
#include <iostream>

DSPGraph::DSPGraph() : nextNodeId(1) {
    ImNodes::CreateContext();
    // 預設建立一些節點
    int synth = addNode(DSPNodeType::Synthesizer, "🎹 Synth");
    int filter = addNode(DSPNodeType::Filter, "🎛️ Filter");
    int mixer = addNode(DSPNodeType::Mixer, "🔊 Mixer");
    addLink(synth, filter);
    addLink(filter, mixer);
}

int DSPGraph::addNode(DSPNodeType type, const std::string& name) {
    int nodeId = nextNodeId++;
    nodes[nodeId] = { nodeId, type, name, {}, {}, 0.5f, 0.5f };
    return nodeId;
}

void DSPGraph::addLink(int from, int to) {
    if (nodes.count(from) && nodes.count(to)) {
        nodes[from].outputs.push_back(to);
        nodes[to].inputs.push_back(from);
        links.emplace_back(from, to);
    }
}

void DSPGraph::render() {
    ImNodes::BeginNodeEditor();

    for (auto& [id, node] : nodes) {
        ImNodes::BeginNode(id);
        ImNodes::BeginNodeTitleBar();
        ImGui::Text("%s", node.name.c_str());
        ImNodes::EndNodeTitleBar();
        
        if (node.type == DSPNodeType::Synthesizer) {
            ImGui::SliderFloat("Freq", &node.param1, 20.0f, 20000.0f);
        } else if (node.type == DSPNodeType::Filter) {
            ImGui::SliderFloat("Cutoff", &node.param1, 20.0f, 20000.0f);
        } else if (node.type == DSPNodeType::Effect) {
            ImGui::SliderFloat("Effect Amount", &node.param1, 0.0f, 1.0f);
        }

        if (!node.inputs.empty()) {
            ImNodes::BeginInputAttribute(id * 2);
            ImGui::Text("Input");
            ImNodes::EndInputAttribute();
        }

        if (!node.outputs.empty()) {
            ImNodes::BeginOutputAttribute(id * 2 + 1);
            ImGui::Text("Output");
            ImNodes::EndOutputAttribute();
        }

        ImNodes::EndNode();
    }

    for (const auto& link : links) {
        ImNodes::Link(link.first, link.first * 2 + 1, link.second * 2);
    }

    ImNodes::EndNodeEditor();
}
