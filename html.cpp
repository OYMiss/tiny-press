//
// Created by OYMiss on 2021/1/6.
//

#include <list>
#include <iostream>
#include "html.h"

using namespace std;

const string HTML_START = "<!DOCTYPE html><html>";
const string HTML_END = "</html>";
const string BODY_START = "<body>";
const string BODY_END = "</body>";
const string HEAD_START = R"(<head><meta charset="utf-8"><title>)";
const string HEAD_END = R"(</title>
<script src="https://polyfill.io/v3/polyfill.min.js?features=es6"></script>
<script id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js"></script>
<link rel="stylesheet" href="/style/style.css"></head>)";
const string HEADER = R"(
<header class="header" id="header">
    <div class="header-wrapper">
        <div class="logo">
            <h1><a href="/">OY's Home</a></h1>
        </div>
        <nav class="main-nav">
            <ul class="menu">
                <li class="menu-item">
                    <a href="/" id="home">
                        <span class="base-name">
                            Home
                        </span>
                    </a>
                </li>
                <li class="menu-item">
                    <a href="/archives" id="archives">
                        <span class="base-name">
                            Archives
                        </span>
                    </a>
                </li>
                <li class="menu-item">
                    <a href="/categories" id="categories">
                        <span class="base-name">
                            Categories
                        </span>
                    </a>
                </li>
                <li class="menu-item">
                    <a href="/about" id="about">
                        <span class="base-name">
                            About
                        </span>
                    </a>
                </li>
            </ul>
        </nav>
    </div>
</header>
)";
const string ARTICLE_START = R"(<article class="markdown-body">)";
const string ARTICLE_END = R"(</article>)";
const string HOMEPAGE_ARTICLE_START = R"(<div class="markdown-body limit-height">)";
const string HOMEPAGE_ARTICLE_END = R"(<div class="hide-article-box"></div></div>)";
const string PAGE_START = R"(<article class="page-body">)";
const string PAGE_END = R"(<article>)";
const string HOMEPAGE_START = R"(<article class="homepage-body">)";
const string HOMEPAGE_END = R"(</article>)";
const string PAGE_HEAD_START = "<h1>";
const string PAGE_HEAD_END = "</h1>";
const string POST_HEAD_START = "<h1>";
const string POST_HEAD_END = "</h1>";

string fill_link(const string &url) {
    return R"(<a class="fill-link" href=")" + url + "\"></a>";
}

string page_link(const string &text, const string &href) {
    return R"(<p class="page-link-container"><a href=")" + href + "\">" + text + "</a></p>";
}

string cat_homepage_item_html(const string &title, const string &content, const string &url) {
    return
            HOMEPAGE_ARTICLE_START +
            POST_HEAD_START + title + POST_HEAD_END +
            content +
            fill_link(url) +
            HOMEPAGE_ARTICLE_END;
}

string cat_content_html(const string &title, const string &content) {
    return
            HTML_START +
            HEAD_START + title + HEAD_END +
            BODY_START +
                HEADER +
                content +
            BODY_END +
            HTML_END;
}

string cat_article_list_html(const string &title, const list<const Article*> &list) {
    string content;
    for (auto article : list) {
        content.append(page_link(article->title, article->url));
    }
    return cat_content_html(title,
                            PAGE_START +
                            PAGE_HEAD_START + title + PAGE_HEAD_END +
                            content +
                            PAGE_END);
}

string cat_article_html(const Article *article) {
    return cat_content_html(article->title,
                            ARTICLE_START +
                            POST_HEAD_START + article->title + POST_HEAD_END +
                            article->html +
                            ARTICLE_END);
}

string cat_homepage_html(const list<const Article*> &article_list) {
    string content;
    int i = 0;
    for (auto article : article_list) {
        content.append(cat_homepage_item_html(article->title, article->html, article->url));
        i ++;
        if (i % 5 == 0) break;
    }
    return cat_content_html("Home",
                            HOMEPAGE_START +
                            content +
                            HOMEPAGE_END);
}


string cat_archives_html(const list<const Article*> &article_list) {
    return cat_article_list_html("归档", article_list);
}

string cat_categories_html(const list<string> &category_list) {
    string content;
    for (const auto &category : category_list) {
        content.append(page_link(category, "/categories/" + category));
    }
    return cat_content_html("分类",
                            PAGE_START +
                            PAGE_HEAD_START + "分类" + PAGE_HEAD_END +
                            content +
                            PAGE_END);
}

string cat_category_articles_html(const string &category_name, const list<const Article*> &article_list) {
    return cat_article_list_html(category_name, article_list);
}
