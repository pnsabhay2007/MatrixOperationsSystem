#include "httplib.h"
#include "Matrix.h"
#include <sstream>
#include <iostream>

// ---- tiny helper to parse "[[1,2],[3,4]]" style JSON arrays without a JSON library ----
std::vector<std::vector<double>> parseMatrixJSON(const std::string& body) {
    std::vector<std::vector<double>> result;
    std::vector<double> row;
    std::string num;
    int depth = 0;
    for (char ch : body) {
        if (ch == '[') { depth++; if (depth == 2) row.clear(); }
        else if (ch == ']') {
            if (!num.empty()) { row.push_back(std::stod(num)); num.clear(); }
            if (depth == 2) result.push_back(row);
            depth--;
        } else if (ch == ',') {
            if (!num.empty()) { row.push_back(std::stod(num)); num.clear(); }
        } else if (isdigit(ch) || ch == '-' || ch == '.') {
            num += ch;
        }
    }
    return result;
}

std::string errorJSON(const std::string& msg) {
    std::ostringstream oss;
    oss << "{\"error\":\"" << msg << "\"}";
    return oss.str();
}

int main() {
    httplib::Server svr;

    // Serve the frontend files from ../web
    svr.set_mount_point("/", "../web");

    // Generic handler: expects JSON body {"a":[[...]],"b":[[...]]}  (b optional for unary ops)
    auto handle = [](const httplib::Request& req, httplib::Response& res, const std::string& op) {
        res.set_header("Access-Control-Allow-Origin", "*");
        try {
            std::string body = req.body;

            // split into "a" and "b" sections crudely by key
            size_t aPos = body.find("\"a\"");
            size_t bPos = body.find("\"b\"");
            std::string aStr = bPos != std::string::npos
                ? body.substr(aPos, bPos - aPos)
                : body.substr(aPos);
            Matrix A(parseMatrixJSON(aStr));

            std::string resultJSON;

            if (op == "add" || op == "subtract" || op == "multiply") {
                if (bPos == std::string::npos) throw std::invalid_argument("Matrix B is required for this operation");
                std::string bStr = body.substr(bPos);
                Matrix B(parseMatrixJSON(bStr));
                Matrix R = (op == "add") ? A + B : (op == "subtract") ? A - B : A * B;
                resultJSON = R.toJSON();
            } else if (op == "transpose") {
                resultJSON = A.transpose().toJSON();
            } else if (op == "determinant") {
                resultJSON = std::to_string(A.determinant());
            } else if (op == "inverse") {
                resultJSON = A.inverse().toJSON();
            } else if (op == "rank") {
                resultJSON = std::to_string(A.rank());
            } else {
                throw std::invalid_argument("Unknown operation");
            }

            res.set_content("{\"result\":" + resultJSON + "}", "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content(errorJSON(e.what()), "application/json");
        }
    };

    svr.Post("/api/add",         [&](const httplib::Request& req, httplib::Response& res){ handle(req, res, "add"); });
    svr.Post("/api/subtract",    [&](const httplib::Request& req, httplib::Response& res){ handle(req, res, "subtract"); });
    svr.Post("/api/multiply",    [&](const httplib::Request& req, httplib::Response& res){ handle(req, res, "multiply"); });
    svr.Post("/api/transpose",   [&](const httplib::Request& req, httplib::Response& res){ handle(req, res, "transpose"); });
    svr.Post("/api/determinant", [&](const httplib::Request& req, httplib::Response& res){ handle(req, res, "determinant"); });
    svr.Post("/api/inverse",     [&](const httplib::Request& req, httplib::Response& res){ handle(req, res, "inverse"); });
    svr.Post("/api/rank",        [&](const httplib::Request& req, httplib::Response& res){ handle(req, res, "rank"); });

    std::cout << "Matrix Operations System server running at http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
    return 0;
}
