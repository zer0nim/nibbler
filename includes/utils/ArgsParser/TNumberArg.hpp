#ifndef TNUMBERARG_HPP_
#define TNUMBERARG_HPP_

#include "AInfoArg.hpp"
#include "ArgsParser.hpp"

// -- NumberArg template -------------------------------------------------------
template<typename T>
class NumberArg : public AInfoArg {
	public:
		NumberArg<T>(ArgsParser *argsParser, std::string name, ArgType::Enum const type)
		: AInfoArg(argsParser, name, type),
		_min(std::numeric_limits<T>::lowest()),
		_max(std::numeric_limits<T>::max()),
		_defaultV({static_cast<T>(0), false}),
		_value({static_cast<T>(0), false}) {
		}

		virtual ~NumberArg<T>() {
		}

		NumberArg<T>(NumberArg<T> const &src) {
			*this = src;
		}

		NumberArg<T>	&operator=(NumberArg<T> const &rhs) {
			AInfoArg::operator=(rhs);
			if (this != &rhs) {
				_min = rhs._min;
				_max = rhs._max;
				_defaultV = rhs._defaultV;
				_value = rhs._value;
			}
			return *this;
		}

		virtual void print(std::ostream &out) const {
			AInfoArg::print(out);

			// print defaut int value
			if (_defaultV.second) {
				out << " " COLOR_L_VAL "default" COLOR_WHITE "=" COLOR_R_VAL <<
					_defaultV.first << COLOR_WHITE;
			}

			// print string min/max
			if (_min != std::numeric_limits<T>::lowest() ||
				_max != std::numeric_limits<T>::max()) {
				out << " " COLOR_L_VAL "range" COLOR_WHITE "=" COLOR_R_VAL "[";
				if (_min != std::numeric_limits<T>::lowest()) {
					out << std::fixed << std::setprecision(3) << _min;
				}
				out << ":";
				if (_max != std::numeric_limits<T>::max()) {
					out << std::fixed << std::setprecision(3) << _max;
				}
				out << "]" COLOR_WHITE;
			}

			out << ">";
		}

		// -- overide virtual parent members -----------------------------------

		// ---- only enabled for floating point --------------------------------
		AInfoArg	&setDefaultF(long double defaultV) {
			if (std::is_floating_point<T>::value) {
				return _setDefault(defaultV);
			}
			return AInfoArg::setDefaultF(defaultV);
		};
		AInfoArg	&setMinF(long double min) {
			if (std::is_floating_point<T>::value) {
				return _setMin(min);
			}
			return AInfoArg::setMinF(min);
		};
		AInfoArg	&setMaxF(long double max) {
			if (std::is_floating_point<T>::value) {
				return _setMax(max);
			}
			return AInfoArg::setMaxF(max);
		};
		// ---- only enabled for signed integral -------------------------------
		AInfoArg	&setDefaultI(int64_t defaultV) {
			if (std::is_integral<T>::value && std::is_signed<T>::value) {
				return _setDefault(defaultV);
			}
			return AInfoArg::setDefaultI(defaultV);
		};
		AInfoArg	&setMinI(int64_t min) {
			if (std::is_integral<T>::value && std::is_signed<T>::value) {
				return _setMin(min);
			}
			return AInfoArg::setMinI(min);
		};
		AInfoArg	&setMaxI(int64_t max) {
			if (std::is_integral<T>::value && std::is_signed<T>::value) {
				return _setMax(max);
			}
			return AInfoArg::setMaxI(max);
		};

		// ---- only enabled for unsigned integral -----------------------------
		AInfoArg	&setDefaultU(uint64_t defaultV) {
			if (std::is_unsigned<T>::value) {
				return _setDefault(defaultV);
			}
			return AInfoArg::setDefaultU(defaultV);
		};
		AInfoArg	&setMinU(uint64_t min) {
			if (std::is_unsigned<T>::value) {
				return _setMin(min);
			}
			return AInfoArg::setMinU(min);
		};
		AInfoArg	&setMaxU(uint64_t max) {
			if (std::is_unsigned<T>::value) {
				return _setMax(max);
			}
			return AInfoArg::setMaxU(max);
		};

		// -- getters ----------------------------------------------------------
		T					getMin() const { return _min; }
		T					getMax() const { return _max; };
		std::pair<T, bool>	getDefaultV() const { return _defaultV; }
		std::pair<T, bool>	getVal() const { return _value; }

		template<typename U>
		void	saveVal(U val) {
			if (val < _min) {
				throw AInfoArgError(std::string("parseArgs(): argument \"" + _name +
					"\": out of range, val:" + std::to_string(val) + " < min:" +
					std::to_string(_min)).c_str());
			}
			else if (val > _max) {
				throw AInfoArgError(std::string("parseArgs(): argument \"" + _name +
					"\": out of range, val:" + std::to_string(val) + " > max:" +
					std::to_string(_max)).c_str());
			}
			else {
				_value = {static_cast<T>(val), true};
			}
		}

		// convert the input string to T
		virtual void		setVal(std::string input);

	private:
		NumberArg<T>();

		// -- templates to avoid code duplication ------------------------------
		AInfoArg	&_setDefault(T defaultV) {
			if (defaultV < _min) {
				throw AInfoArgError(std::string("argument \"" + _name + "\": setDefault(): default:" +
					std::to_string(defaultV) + " < min:" + std::to_string(_min)).c_str());
			}
			else if (defaultV > _max) {
				throw AInfoArgError(std::string("argument \"" + _name + "\": setDefault(): default:" +
					std::to_string(defaultV) + " > max:" + std::to_string(_max)).c_str());
			}
			else {
				this->_defaultV = {defaultV, true};
				_value = {defaultV, true};  // update _value accordingly
			}
			return *this;
		};

		AInfoArg	&_setMin(T min) {
			if (_defaultV.second && _defaultV.first < min) {
				throw AInfoArgError(std::string("argument \"" + _name + "\": setMin(): min:" +
					std::to_string(min) + " > default:" + std::to_string(_defaultV.first)).c_str());
			}
			else {
				this->_min = min;
			}
			return *this;
		};

		AInfoArg	&_setMax(T max) {
			if (_defaultV.second && _defaultV.first > max) {
				throw AInfoArgError(std::string("argument \"" + _name + "\": setMax(): max:" +
					std::to_string(max) + " < default:" + std::to_string(_defaultV.first)).c_str());
			}
			else {
				this->_max = max;
			}
			return *this;
		};


		T					_min;
		T					_max;
		std::pair<T, bool>	_defaultV;
		std::pair<T, bool>	_value;
};


// -- convertVal template function definition and declaration ------------------
// uses specialization to manage conversion

// floating point specification
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
convertVal(NumberArg<T> *ref, std::string input) {
	long double val = std::stold(input);
	ref->template saveVal<long double>(val);
}

// signed integral specification
template <typename T>
typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value, void>::type
convertVal(NumberArg<T> *ref, std::string input) {
	int64_t	val = std::stoll(input);
	ref->template saveVal<int64_t>(val);
}

// unsigned integral specification
template <typename T>
typename std::enable_if<std::is_unsigned<T>::value, void>::type
convertVal(NumberArg<T> *ref, std::string input) {
	// first cast input to double to detect out of range
	double	dVal = std::stod(input);
	if (dVal < 0 || dVal > std::numeric_limits<uint64_t>::max()) {
		throw std::out_of_range("out of range input");
	}
	// reconvert again for precision
	uint64_t val = std::stoull(input);
	ref->template saveVal<uint64_t>(val);
}


// -- setVal definition --------------------------------------------------------
// we need to define setVal after convertVal declaration to avoid circular dependencies
template<typename T>
void	NumberArg<T>::setVal(std::string input) {
	try {
		convertVal<T>(this, input);
	}
	catch (const std::out_of_range &e) {
		throw AInfoArgError(std::string("parseArgs(): argument \"" + _name +
			"\": out of range input \"" + input + "\"").c_str());
	}
	catch (const std::invalid_argument &e) {
		throw AInfoArgError(std::string("parseArgs(): argument \"" + _name +
			"\": failed to convert input \"" + input + "\"").c_str());
	}
}

#endif  // TNUMBERARG_HPP_
