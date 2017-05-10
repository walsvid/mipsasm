#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::blue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\badd\\b" << "\\baddu\\b" << "\\baddi\\b" << "\\baddiu\\b"
                    << "\\band\\b" << "\\bandi\\b"
                    << "\\bdiv\\b" << "\\bdivu\\b"
                    << "\\bmult\\b" << "\\bmultu\\b"
                    << "\\bnor\\b"
                    << "\\bor\\b" << "\\bori\\b"
                    << "\\bsll\\b" << "\\bsllv\\b"
                    << "\\bsra\\b" << "\\bsrav\\b"
                    << "\\bsrl\\b" << "\\bsrlv\\b"
                    << "\\bsub\\b" << "\\bsubu\\b"
                    << "\\bxor\\b" << "\\bxori\\b"
                    << "\\blhi\\b"
                    << "\\bllo\\b"
                    << "\\bslt\\b" << "\\bsltu\\b" << "\\bslti\\b" << "\\bsltiu\\b"
                    << "\\bbeq\\b"
                    << "\\bbgtz\\b"
                    << "\\bblez\\b"
                    << "\\bbne\\b"
                    << "\\bj\\b" << "\\bjal\\b" << "\\bjalr\\b" << "\\bjr\\b"
                    << "\\blb\\b" << "\\blbu\\b" << "\\blh\\b" << "\\blhu\\b" << "\\blw\\b"
                    << "\\bsb\\b" << "\\bsh\\b" << "\\bsw\\b"
                    << "\\bmfhi\\b" << "\\bmflo\\b" << "\\bmthi\\b" << "\\bmtlo\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    immediateNumberFormat.setFontWeight(QFont::Bold);
    immediateNumberFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\\b[0-9]+\\b");
    rule.format = immediateNumberFormat;
    highlightingRules.append(rule);

    regFormat.setFontWeight(QFont::Bold);
    regFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\B\\$[0-9]{1,2}\\b");
    rule.format = regFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::darkRed);
    rule.pattern = QRegExp("#[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);



//    multiLineCommentFormat.setForeground(Qt::red);

//    quotationFormat.setForeground(Qt::darkGreen);
//    rule.pattern = QRegExp("\".*\"");
//    rule.format = quotationFormat;
//    highlightingRules.append(rule);

//    functionFormat.setFontItalic(true);
//    functionFormat.setForeground(Qt::blue);
//    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
//    rule.format = functionFormat;
//    highlightingRules.append(rule);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
