#include <iostream>
#include <filesystem>
#include <map>
#include <list>
#include "lib/convert.hpp"
#include "html.h"

namespace fs = std::filesystem;

std::string output_root = "./output";

void save(const std::string &content, const std::string &path) {
    std::ofstream out;
    out.open(path);
    out << content;
    out.close();
}

std::string trim(const std::string &s) {
    int i = 0;
    while (i < s.length() and s[i] == ' ') i++;
    auto j = s.length() - 1;
    while (j > i and s[j] == ' ') j--;
    return s.substr(i, j - i + 1);
}

void process_article_info(std::map<std::string, std::string> &info, std::ifstream &fin) {
    std::string buffer;
    bool info_begin = false;
    while (getline(fin, buffer)) {
        if (buffer.substr(0, 3) == "---") {
            if (info_begin) break;
            info_begin = true;
            continue;
        }
        int i = 0;
        while (i < buffer.length() and buffer[i] != ':') i++;
        if (buffer[i] == ':') {
            info[trim(buffer.substr(0, i))] = trim(buffer.substr(i + 1));
        }
    }
}

std::string generate_article(std::ifstream &fin, const std::map<std::string, std::string> &info, const std::string &output_path) {
    auto content = to_html(fin);
    auto cached_homepage_item = cat_homepage_item_html(info.at("title"), content, info.at("url"));
    save(cat_markdown_page_html(info.at("title"), content), output_path);
    return cached_homepage_item;
}

void generate_list(const std::string &title, const std::string &url, const std::list<std::pair<std::string, std::string>> &list) {
    // url = /archives
    std::string s;
    for (auto [text, href] : list) {
        s.append(page_link(text, href));
    }
    auto p = output_root + url;
    if (fs::exists(p) or fs::create_directories(p)) {
        save(cat_page_html(title, s), p + "/index.html");
    }
}

void generate_archives(const std::list<std::pair<std::string, std::string>> &list) {
    generate_list("归档", "/archives", list);
}

void generate_categories(const std::map<std::string, std::list<std::pair<std::string, std::string>>> &category_map) {
    std::string s;
    for (auto [text, list] : category_map) {
        s.append(page_link(text, "/categories/" + text));
        generate_list(text, "/categories/" + text, list);
    }
    if (fs::exists(output_root + "/categories") or fs::create_directories(output_root + "/categories")) {
        save(cat_page_html("类别", s), output_root + "/categories/index.html");
    }
}

void generate_homepage(const std::list<std::pair<std::string, std::string>> &list) {
    std::string s;
    int i = 0;
    for (auto [url, article_content] : list) {
        s.append(article_content);
        i ++;
        if (i % 3 == 0) break;
    }
    save(cat_homepage_html(s), output_root + "/index.html");
}

void generate(const std::string &path) {
    std::list<std::pair<std::string, std::string>> post_list;
    std::map<std::string, std::list<std::pair<std::string, std::string>>> category_map;
    std::list<std::pair<std::string, std::string>> homepage_list;
    if (not fs::exists(path)) {
        std::cout << "wrong path" << std::endl;
        exit(1);
    }

    for (const auto & entry : fs::recursive_directory_iterator(path)) {
        if (not entry.is_directory()) {
            const auto& file = entry.path();
            if (file.extension() == ".md") {
                // 获取路径信息
                auto s1 = file.parent_path().string();
                auto url = file.parent_path().string().substr(path.length() - 1) + "/" + file.stem().string();
                auto output_directory = output_root + file.parent_path().string().substr(path.length() - 1) + "/" + file.stem().string();
                if (fs::exists(output_directory) or fs::create_directories(output_directory)) {
                    std::map<std::string, std::string> info;
                    std::ifstream fin(file.string());
                    // 处理分类、标题、日期等信息
                    process_article_info(info, fin);
                    category_map[info.at("categories")].emplace_back(info.at("title"), url);
                    post_list.emplace_back(info.at("title"), url);
                    info["url"] = url;
                    // 生成文章详情页
                    auto article_content = generate_article(fin, info, output_directory + "/" + "index.html");
                    homepage_list.emplace_back(url, article_content);
                    fin.close();
                } else {
                    std::cout << file.parent_path() << std::endl;
                    std::cout << "ERROR!!" << std::endl;
                }
            }
        }
    }
    generate_homepage(homepage_list);
    generate_archives(post_list);
    generate_categories(category_map);
}

// tiny_press -i ./post/ -o /usr/local/var/www
int main (int argc, char const *argv[]) {
    std::string path = "./post";

    if (argc == 2) {
        path = argv[1];
    } else {
        for (unsigned i = 1; i < argc; i++) {
            if (std::string(argv[i]) == "-o") {
                output_root = argv[i + 1];
            } else if (std::string(argv[i]) == "-i") {
                path = argv[i + 1];
            }
        }
    }

    if (path.back() != '/') path.push_back('/');
    generate(path);

    std::cout << "Current path is " << fs::current_path() << '\n';
    std::cout << "Input path is " << path << '\n';
    std::cout << "Output path is " << output_root << '\n';
}

