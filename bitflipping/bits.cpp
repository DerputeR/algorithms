#include <iostream>
#include <algorithm>
#include <string>
#include <cstdint>
#include <cmath>

void recv(const std::string& msg, uint32_t from, uint32_t to, int time) {
    std::cout << time << ": Processor " << to << " received " << msg << " from processor " << from << std::endl;
}

void send(const std::string& msg, uint32_t from, uint32_t to, int time) {
    std::cout << time << ": Processor " << from << " sent " << msg << " to processor " << to << std::endl;
}

/**
 * @brief Simulates MPI_Broadcast with a p-core CPU
 * @param msg the message to broadcast
 * @param root rank of the root processor
 * @param rank rank of the current sending processor
 * @param time tracks what time this step is at
 * @param p number of processors available (no more than 32)
 */
void broadcast(const std::string& msg, uint32_t root, uint32_t rank, uint8_t p, int time) {
    uint32_t d = std::log2(std::min(p, static_cast<uint8_t>(32))); // number of bits needed to represent the maximum rank
    uint32_t flip = 1 << (d - 1); // start bit flips at MSB
    uint32_t mask = flip - 1; // mask to check all bits right of flip
    for (int j = (d - 1); j >= 0; j--) {
        if (((rank ^ root) & mask) == 0) {
            if (((rank ^ root) & flip) == 0) {
                send("msg", rank, (((rank ^ root) ^ flip) ^ root), time);
                // since we're running in serial we have to treat this as serial D&C
                broadcast(msg, root, (((rank ^ root) ^ flip) ^ root), p, time + 1);
            } else {
                recv("msg", (((rank ^ root) ^ flip) ^ root), rank, time);
            }
        }
        time++;
        mask = mask >> 1;
        flip = flip >> 1;
    }
}

int main(int argc, char* argv[]) {
    broadcast("msg", 0, 0, 8, 0);
    return 0;
}
