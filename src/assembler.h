#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QDebug>
#include <QRegExp>

class Assembler
{

public:
    Assembler();
    QString Compile(QString& stringNeedCompile);
    QStringList Lexer(QString& stringNeedCompile);
    QString getRawAssembledString(QStringList& rawAssembledStringList);
    QString validInstructionToMachineCode(QString currentLine);
    void convert_Reg_S(const QString& rs, QString& machineCodeNeedConvert);
    void convert_Reg_T(const QString& rt, QString& machineCodeNeedConvert);
    void convert_Reg_D(const QString& rd, QString& machineCodeNeedConvert);
    void convert_ShiftAmount(const QString& sa, QString& machineCodeNeedConvert);
    void convert_Immediate(const QString& imm, QString& machineCodeNeedConvert);
    void convert_Target(const QString& target, QString& machineCodeNeedConvert);

private:
    QString rawAssembledString;
    QMap<QString, QString> keywordOpCode;
    QStringList keywordPatterns;

    QStringList R_InstructionPatterns;
    QStringList R_STD_InstructionPatterns;
    QStringList R_ST__InstructionPatterns;
    QStringList R_TDA_InstructionPatterns;
    QStringList R_SD__InstructionPatterns;
    QStringList R_S___InstructionPatterns;

    QStringList I_InstructionPatterns;
    QStringList I_STI_InstructionPatterns;
    QStringList I_SI__InstructionPatterns;

    QStringList J_InstructionPatterns;

    QStringList resultList;
};

#endif // ASSEMBLER_H
