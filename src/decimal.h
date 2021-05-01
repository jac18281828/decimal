#pragma once

#include <string>
#include <cstdint>

namespace dec {

class Decimal {
public:
    using value_t = int64_t;
    using expt_t  = int16_t;

private:
    Decimal(const value_t mantissa, const expt_t exponent) : m_mantissa(mantissa), m_exponent(exponent) {}

public:

    Decimal() = default;
    Decimal(std::string const& value) : m_mantissa(0L), m_exponent(0) {

        if(value.length() <= 16) {

        constexpr auto IAZ = '0';
        constexpr auto DOT = '.';

        value_t pow = 1;
        bool has_dot = false;
        bool has_val = false;

        expt_t exponent = 0;

        auto add_char = [&](const auto d) {
            if(d == DOT) {
                has_dot=true;
            } else {
                const auto val = d - IAZ;
                if(val != 0 || has_val) {
                    has_val = true;
                    m_mantissa += val * pow;
                    pow *= 10L;
                }
                if(!has_dot && has_val) exponent--;
            }
        };
        
        std::for_each(std::rbegin(value), std::rend(value), add_char);

        if(has_dot) m_exponent = exponent;

        } else {
            throw std::runtime_error("overflow");
        }
    }

    bool operator==(Decimal const& decimal) const {
        return m_mantissa == decimal.normalize(m_exponent);
    }

    value_t mantissa() const { return m_mantissa; }
    expt_t exponent() const { return m_exponent; }

    value_t normalize(expt_t expt) const {
        value_t val = m_mantissa;
        while(expt < m_exponent) {
            val *= 10L;
            expt += 1;
        }
        while(expt > m_exponent) {
            val /= 10L;
            expt -= 1;
        }
        return val;
    }

    Decimal operator+(Decimal const& decimal) const {
        if(m_exponent < decimal.exponent()) {
            return Decimal(m_mantissa + decimal.normalize(m_exponent), m_exponent);
        } else {
            return Decimal(normalize(decimal.m_exponent) + decimal.m_mantissa, decimal.m_exponent);
        }
    }

    Decimal& operator+=(Decimal const& decimal) {
        if(m_exponent < decimal.exponent()) {
            m_mantissa += decimal.normalize(m_exponent);
        } else {
            m_mantissa = normalize(decimal.m_exponent) + decimal.m_mantissa;
            m_exponent = decimal.m_exponent;
        }
        return *this;
    }

    Decimal operator*(Decimal const& decimal) const {
        auto expt = m_exponent + decimal.m_exponent;
        return Decimal(m_mantissa * decimal.m_mantissa, expt);
    }

    Decimal& operator*=(Decimal const& decimal) {
        m_exponent += decimal.m_exponent;
        m_mantissa *= decimal.m_mantissa;
        return *this;
    }

    Decimal operator/(Decimal const& decimal) const {
        auto expt = m_exponent - decimal.m_exponent;
        return Decimal(m_mantissa / decimal.m_mantissa, expt);
    }

private:
    value_t m_mantissa;
    expt_t  m_exponent;

};

}
