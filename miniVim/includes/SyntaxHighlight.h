#ifndef SYNTAXHIGHLIGHT_H
#define SYNTAXHIGHLIGHT_H

#include <qchar.h>
#include <qobjectdefs.h>
#include <qtextdocument.h>
#include <qtextformat.h>
#include <qsyntaxhighlighter.h>
#include <qregularexpression.h>

class SyntaxHighlight : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    SyntaxHighlight(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QList<HighlightingRule> highlightingRules;

    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};

#endif
