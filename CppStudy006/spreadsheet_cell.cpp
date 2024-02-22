module spreadsheet_cell;

using namespace std;

namespace spreadsheet01
{
    void SpreadsheetCell::setColor(const Color color) { this->color = color; }
    auto SpreadsheetCell::getColor() const -> Color { return color; }

    std::string SpreadsheetCell::doubleToString(const double value) {
        return std::to_string(value);
    }
    double SpreadsheetCell::stringToDouble(const std::string_view inString) {
        try {
            return std::stod(std::string(inString));
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
            return 0.0;
        }
    }

    SpreadsheetCell::SpreadsheetCell(const double initial_value) : value{ initial_value } {}
    SpreadsheetCell::SpreadsheetCell(const std::string_view initial_value) { setValue(initial_value); }

    void SpreadsheetCell::setValue(const double value) {
        this->value = value;
        printCell(*this);
    }
    double SpreadsheetCell::getValue() const {
        numAccesses++; // mutable keyword p.464
        return value;
    }

    void SpreadsheetCell::setValue(const std::string_view inString) { value = stringToDouble(inString); }
    std::string SpreadsheetCell::getString() const {
        numAccesses++;
        return doubleToString(value);
    }

    void SpreadsheetCell::printCell(const SpreadsheetCell& cell) {
        cout << cell.getString() << endl;
    }
    void SpreadsheetCell::printCell() const { cout << this->getString() << endl; }

    SpreadsheetCell SpreadsheetCell::add(const SpreadsheetCell& cell) const
    {
        return SpreadsheetCell{ getValue() + cell.getValue() };
    }

    SpreadsheetCell SpreadsheetCell::operator+(const double rhs) const {
        return SpreadsheetCell{ getValue() + rhs };
    }

    SpreadsheetCell SpreadsheetCell::operator/(const SpreadsheetCell& cell) const {
        if (cell.getValue() == 0) {
            throw invalid_argument{ "Dvide by zero \u25A1" };
        }
        return SpreadsheetCell{ getValue() / cell.getValue() };
    }

    SpreadsheetCell SpreadsheetCell::operator-(const SpreadsheetCell& cell) const {
        return SpreadsheetCell{ getValue() - cell.getValue() };
    }

    SpreadsheetCell SpreadsheetCell::operator*(const SpreadsheetCell& cell) const {
        return SpreadsheetCell{ getValue() * cell.getValue() };
    }

    SpreadsheetCell& SpreadsheetCell::operator+=(const SpreadsheetCell& rhs) {
        setValue(getValue() + rhs.getValue());
        return *this;
    }
    SpreadsheetCell& SpreadsheetCell::operator-=(const SpreadsheetCell& rhs) {
        setValue(getValue() - rhs.getValue());
        return *this;
    }
    SpreadsheetCell& SpreadsheetCell::operator*=(const SpreadsheetCell& rhs) {
        setValue(getValue() * rhs.getValue());
        return *this;
    }
    SpreadsheetCell& SpreadsheetCell::operator/=(const SpreadsheetCell& rhs) {
        if (rhs.getValue() == 0) throw invalid_argument{ "Dvide by zero \u25A1" };
        setValue(getValue() / rhs.getValue());
        return *this;
    }
}