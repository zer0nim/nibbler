#ifndef TNUMBERARG_HPP_
#define TNUMBERARG_HPP_

#include "AInfoArg.hpp"

template<typename T>
class NumberArg : public AInfoArg {
	public:
		NumberArg<T>(ArgsParser *argsParser, std::string name)
		: AInfoArg(argsParser, name, ArgType::INT32),
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
		AInfoArg	&setDefaultF(double defaultV) {
			if (std::is_floating_point<T>::value) {
				return _setDefault(defaultV);
			}
			return AInfoArg::setDefaultF(defaultV);
		};
		AInfoArg	&setMinF(double min) {
			if (std::is_floating_point<T>::value) {
				return _setMin(min);
			}
			return AInfoArg::setMinF(min);
		};
		AInfoArg	&setMaxF(double max) {
			if (std::is_floating_point<T>::value) {
				return _setMin(max);
			}
			return AInfoArg::setMaxF(max);
		};
		// ---- only enabled for signed integral -------------------------------
		AInfoArg	&setDefaultI(int64_t defaultV) {
			if (std::is_floating_point<T>::value) {
				return _setDefault(defaultV);
			}
			return AInfoArg::setDefaultI(defaultV);
		};
		AInfoArg	&setMinI(int64_t min) {
			if (std::is_floating_point<T>::value) {
				return _setMin(min);
			}
			return AInfoArg::setMinI(min);
		};
		AInfoArg	&setMaxI(int64_t max) {
			if (std::is_floating_point<T>::value) {
				return _setMin(max);
			}
			return AInfoArg::setMaxI(max);
		};

		// ---- only enabled for unsigned integral -----------------------------
		AInfoArg	&setDefaultU(uint64_t defaultV) {
			if (std::is_floating_point<T>::value) {
				return _setDefault(defaultV);
			}
			return AInfoArg::setDefaultU(defaultV);
		};
		AInfoArg	&setMinU(uint64_t min) {
			if (std::is_floating_point<T>::value) {
				return _setMin(min);
			}
			return AInfoArg::setMinU(min);
		};
		AInfoArg	&setMaxU(uint64_t max) {
			if (std::is_floating_point<T>::value) {
				return _setMin(max);
			}
			return AInfoArg::setMaxU(max);
		};

		// -- getters ----------------------------------------------------------
		T					getMin() const { return _min; }
		T					getMax() const { return _max; };
		std::pair<T, bool>	getDefaultV() const { return _defaultV; }
		std::pair<T, bool>	getVal() const { return _value; }


		// convert the input string to T
		virtual void		setVal(std::string input) {
			T	val = 0;
			try {
				val = std::stoi(input);

				if (val < _min) {
					logErr("parseArgs(): argument \"" << _name << "\": out of range, val:"
						<< val << " < min:" << _min);
				}
				else if (val > _max) {
					logErr("parseArgs(): argument \"" << _name << "\": out of range, val:"
						<< val << " > max:" << _max);
				}
				else {
					_value = {val, true};
				}
			}
			catch (const std::out_of_range &e) {
				logErr("parseArgs(): argument \"" << _name << "\": out of range input \""
					<< input << "\"");
			}
			catch (const std::invalid_argument &e) {
				logErr("parseArgs(): argument \"" << _name << "\": failed to convert input \""
					<< input << "\"");
			}
		}

	private:
		NumberArg<T>();

		// templates to avoid code duplication
		AInfoArg	&_setDefault(T defaultV) {
			if (defaultV < _min) {
				logErr("argument \"" << _name << "\": setDefault(): default:" <<
					defaultV << " < min:" << _min);
				throw AInfoArgError("setDefault() error");
			}
			else if (defaultV > _max) {
				logErr("argument \"" << _name << "\": setDefault(): default:" <<
					defaultV << " > max:" << _max);
				throw AInfoArgError("setDefault() error");
			}
			else {
				this->_defaultV = {defaultV, true};
				_value = {defaultV, true};  // update _value accordingly
			}
			return *this;
		};

		AInfoArg	&_setMin(T min) {
			if (_defaultV.second && _defaultV.first < min) {
				logErr("argument \"" << _name << "\": setMin(): min:" << min <<
					" > default:" << _defaultV.first);
				throw AInfoArgError("setMin() error");
			}
			else {
				this->_min = min;
			}
			return *this;
		};

		AInfoArg	&_setMax(T max) {
			if (_defaultV.second && _defaultV.first > max) {
				logErr("argument \"" << _name << "\": setMax(): max:" << max <<
					" < default:" << _defaultV.first);
				throw AInfoArgError("setMax() error");
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

#endif  // TNUMBERARG_HPP_
