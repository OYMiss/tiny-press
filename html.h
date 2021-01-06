//
// Created by OYMiss on 2021/1/6.
//

#ifndef MARKTOOL_HTML_H
#define MARKTOOL_HTML_H

const std::string HTML_START = "<!DOCTYPE html><html>";
const std::string HTML_END = "</html>";
const std::string BODY_START = "<body>";
const std::string BODY_END = "</body>";
const std::string HEAD_START = R"(<head><meta charset="utf-8"><title>)";
const std::string HEAD_END = R"(</title>
<script src="https://polyfill.io/v3/polyfill.min.js?features=es6"></script>
<script id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js"></script>
<link rel="stylesheet" href="/style/style.css"></head>)";
const std::string HEADER = R"(
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
                    <a href="javascript:;" id="tags">
                        <span class="base-name">
                            Tags
                        </span>
                    </a>
                </li>
            </ul>
        </nav>
    </div>
</header>
)";
const std::string ARTICLE_START = R"(<article class="markdown-body">)";
const std::string ARTICLE_END = R"(</article>)";
const std::string HOMEPAGE_ARTICLE_START = R"(<div class="markdown-body limit-height">)";
const std::string HOMEPAGE_ARTICLE_END = R"(<div class="hide-article-box"></div></div>)";
const std::string PAGE_START = R"(<article class="page-body">)";
const std::string PAGE_END = R"(<article>)";
const std::string HOMEPAGE_START = R"(<article class="homepage-body">)";
const std::string HOMEPAGE_END = R"(</article>)";
const std::string PAGE_HEAD_START = "<h1>";
const std::string PAGE_HEAD_END = "</h1>";
const std::string POST_HEAD_START = "<h1>";
const std::string POST_HEAD_END = "</h1>";


std::string page_link(const std::string &text, const std::string &href);

std::string cat_homepage_item_html(const std::string &title, const std::string &content, const std::string &url);

std::string cat_markdown_page_html(const std::string &title, const std::string &content);

std::string cat_page_html(const std::string &title, const std::string &content);

std::string cat_homepage_html(const std::string &content);

#endif //MARKTOOL_HTML_H
