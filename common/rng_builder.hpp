#pragma once

#include <memory>
#include <random>

class RngBuilder {
public:
    static RngBuilder& getInstance() {
        static RngBuilder instance;
        return instance;
    }

    auto getInteger() noexcept { return (*m_dist)(m_rd); }

private:
    RngBuilder() noexcept {
        m_regen = std::make_shared<std::mt19937>(m_rd());
        m_dist = std::make_shared<std::uniform_int_distribution<std::size_t>>(
            (0, std::random_device::max()));
    }

    std::random_device m_rd;
    std::shared_ptr<std::mt19937> m_regen;
    std::shared_ptr<std::uniform_int_distribution<std::size_t>> m_dist;
};

#define RAND_INT(x) (RngBuilder::getInstance().getInteger() % x)
