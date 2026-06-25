#include "workload_manager.h"
#include <iostream>
#include <algorithm>

namespace nanoai {
namespace cluster {

WorkloadManager& WorkloadManager::getInstance() {
    static WorkloadManager instance;
    return instance;
}

std::vector<WorkloadChunk> WorkloadManager::splitWorkload(const std::string& input, int chunkCount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<WorkloadChunk> chunks;
    if (chunkCount <= 0) chunkCount = 1;

    size_t chunkSize = input.length() / chunkCount;
    if (chunkSize == 0) chunkSize = input.length();

    for (int i = 0; i < chunkCount; ++i) {
        size_t start = i * chunkSize;
        if (start >= input.length()) break;

        size_t end = (i == chunkCount - 1) ? input.length() : (i + 1) * chunkSize;

        WorkloadChunk chunk;
        chunk.chunkId = "chunk_" + std::to_string(i);
        chunk.data = input.substr(start, end - start);
        chunk.sequenceNumber = i;
        chunks.push_back(chunk);
    }

    std::cout << "WorkloadManager: Split input into " << chunks.size() << " chunks." << std::endl;
    return chunks;
}

void WorkloadManager::distributeWorkload(const std::vector<WorkloadChunk>& chunks, const std::vector<std::string>& nodeIds) {
    if (nodeIds.empty()) {
        std::cout << "WorkloadManager: No nodes available for distribution." << std::endl;
        return;
    }

    for (size_t i = 0; i < chunks.size(); ++i) {
        std::string targetNode = nodeIds[i % nodeIds.size()];
        std::cout << "WorkloadManager: Sending " << chunks[i].chunkId << " to node " << targetNode << std::endl;
    }
}

std::string WorkloadManager::assembleWorkload(const std::vector<WorkloadChunk>& chunks) {
    std::vector<WorkloadChunk> sortedChunks = chunks;
    std::sort(sortedChunks.begin(), sortedChunks.end(), [](const auto& a, const auto& b) {
        return a.sequenceNumber < b.sequenceNumber;
    });

    std::string result;
    for (const auto& chunk : sortedChunks) {
        result += chunk.data;
    }
    return result;
}

} // namespace cluster
} // namespace nanoai
