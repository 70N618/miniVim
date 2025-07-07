#include "../includes/SyntaxHighlight.h"
#include <qnamespace.h>

SyntaxHighlight::SyntaxHighlight(QTextDocument *parent): QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    // Set keywords style

    keywordFormat.setForeground(Qt::green);
    keywordFormat.setFontWeight(QFont::Bold);

    // Here we just build up our keywords array of string.

    const QString keywordPatterns[] =
    {
        QStringLiteral("\\bchar\\b"), QStringLiteral("\\bclass\\b"), QStringLiteral("\\bconst\\b"),
        QStringLiteral("\\bdouble\\b"), QStringLiteral("\\benum\\b"), QStringLiteral("\\bexplicit\\b"),
        QStringLiteral("\\bfriend\\b"), QStringLiteral("\\binline\\b"), QStringLiteral("\\bint\\b"),
        QStringLiteral("\\blong\\b"), QStringLiteral("\\bnamespace\\b"), QStringLiteral("\\boperator\\b"),
        QStringLiteral("\\bprivate\\b"), QStringLiteral("\\bprotected\\b"), QStringLiteral("\\bpublic\\b"),
        QStringLiteral("\\bshort\\b"), QStringLiteral("\\bsignals\\b"), QStringLiteral("\\bsigned\\b"),
        QStringLiteral("\\bslots\\b"), QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstruct\\b"),
        QStringLiteral("\\btemplate\\b"), QStringLiteral("\\btypedef\\b"), QStringLiteral("\\btypename\\b"),
        QStringLiteral("\\bunion\\b"), QStringLiteral("\\bunsigned\\b"), QStringLiteral("\\bvirtual\\b"),
        QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bvolatile\\b"), QStringLiteral("\\bbool\\b")
    };

    // For loop that iterates each pattern in keyword patterns
    // A rule is composed by a pattern and a format (style)
    // Once a rule is filled, we append it to our rules list

    for (const QString &pattern : keywordPatterns)
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Matches any String starting with Q
    // /b is for checking if string is preeced by non word char (chars, num and '_')
    // in between needs to be chars ranging from a-z and A-Z
    // + match one or more of preceding tokens.

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::magenta);
    rule.pattern = QRegularExpression(QStringLiteral("\\bQ[A-Za-z]+\\b"));
    rule.format = classFormat;
    highlightingRules.append(rule);


    // i.e "NRM" -> matches any char except line breaks.
    // Match 0 or  more of preceding token "." in this case.

    quotationFormat.setForeground(Qt::cyan);
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    // Match any function that has
    // non word char before it \b
    // from a-z A-Z 0-9 and _ after that
    // + matches one or more previous tokens
    // (?=\\()) -> positive look ahead. we're checking after the expression
    // inside the square brackets, there is an open parenthesis, but we're not
    // including it

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::yellow);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.format = functionFormat;
    highlightingRules.append(rule);

    // Matches // and 0 or more chars that are not new line

    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);

    // For the time being we only assign expressions for multiline comment

    commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
}

void SyntaxHighlight::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : std::as_const(highlightingRules))
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    // Handle multi line comments /* i.e
    //                                hello world */

    // 0 means outside of comment, 1 means inside

    // "if the previous block state was "in comment" (previousBlockState() == 1),
    // we start the search for an end expression at the beginning of the text block.
    // If the previousBlockState() returns 0,
    // we start the search at the location of the first occurrence of a start expression."

    int startIndex = 0;

    // If we're not inside a comment, we must find the index of the expression /*

    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);
    while (startIndex >= 0)
    {
      // look for */ starting from match

      QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
      int endIndex = match.capturedStart(); // store endIndex
      int commentLength = 0;

      // if it's -1 it means we're still inside a comment block, no */ found

      if (endIndex == -1)
      {
          // Set currentBLockState to 1. We're inside a comment

          setCurrentBlockState(1);
          commentLength = text.length() - startIndex;
      }
      else
      {
          // We found the end of the comment block. So we get end - start + lenght of */

          commentLength = endIndex - startIndex + match.capturedLength();
      }

      // Set format from start index, for commengtLength using multiLineCommentFormat

      setFormat(startIndex, commentLength, multiLineCommentFormat);

      // StartIndex will now be equal to, startIndex + commentLength, starting from cStartExpression

      startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
