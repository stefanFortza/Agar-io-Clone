//
// Created by stefantacu on 20.03.2024.
//

#include "../../headers/utils/Signal.h"
//
// template<>
// void Signal<>::connect(const SlotType &slot) {
//     m_slots.push_back(slot);
// }
//
// template<typename... Args>
// void Signal<Args...>::disconnect(const SlotType &slot) {
//     m_slots.erase(std::remove(m_slots.begin(), m_slots.end(), slot), m_slots.end());
// }
//
// template<typename... Args>
// void Signal<Args...>::emit(Args... args) {
//     for (const auto &slot: m_slots) {
//         slot(args...);
//     }
// }
//
//
