//
// Created by stefantacu on 20.03.2024.
//

#ifndef SUBJECT_H
#define SUBJECT_H
#include <functional>
#include <iostream>
#include <vector>

template<typename... Args>
class Signal {
public:
    using SlotType = std::function<void(Args...)>;

    void connect(const SlotType &slot) {
        std::cout << "connect\n";
        m_slots.push_back(slot);
    }

    void disconnect(const SlotType &slot) {
        m_slots.erase(std::remove(m_slots.begin(), m_slots.end(), slot), m_slots.end());
    }

    void emit(Args... args) {
        std::cout << "emit\n";
        for (const auto &slot: m_slots) {
            slot(args...);
        }
    }

private:
    std::vector<SlotType> m_slots;
};


#endif //SUBJECT_H
