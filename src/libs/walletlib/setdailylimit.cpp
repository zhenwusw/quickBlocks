/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *
 * The LICENSE at the root of this repo details your rights (if any)
 *------------------------------------------------------------------------*/
/*
 * This file was generated with makeClass. Edit only those parts of the code inside
 * of 'EXISTING_CODE' tags.
 */
#include "setdailylimit.h"
#include "etherlib.h"

//---------------------------------------------------------------------------
IMPLEMENT_NODE(QSetDailyLimit, CTransaction, dataSchema());

//---------------------------------------------------------------------------
static SFString nextSetdailylimitChunk(const SFString& fieldIn, const void *data);
static SFString nextSetdailylimitChunk_custom(const SFString& fieldIn, const void *data);

//---------------------------------------------------------------------------
void QSetDailyLimit::Format(CExportContext& ctx, const SFString& fmtIn, void *data) const {
    if (!m_showing)
        return;

    if (fmtIn.empty()) {
        ctx << toJson();
        return;
    }

    SFString fmt = fmtIn;
    if (handleCustomFormat(ctx, fmt, data))
        return;

    while (!fmt.empty())
        ctx << getNextChunk(fmt, nextSetdailylimitChunk, this);
}

//---------------------------------------------------------------------------
SFString nextSetdailylimitChunk(const SFString& fieldIn, const void *data) {
    const QSetDailyLimit *set = (const QSetDailyLimit *)data;
    if (set) {
        // Give customized code a chance to override first
        SFString ret = nextSetdailylimitChunk_custom(fieldIn, data);
        if (!ret.empty())
            return ret;

        switch (tolower(fieldIn[0])) {
            case '_':
                if ( fieldIn % "_newLimit" ) return asStringBN(set->_newLimit);
                break;
        }

        // EXISTING_CODE
        // EXISTING_CODE

        // Finally, give the parent class a chance
        ret = nextTransactionChunk(fieldIn, set);
        if (!ret.empty())
            return ret;
    }

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------------------------------
bool QSetDailyLimit::setValueByName(const SFString& fieldName, const SFString& fieldValue) {
    // EXISTING_CODE
    // EXISTING_CODE

    if (CTransaction::setValueByName(fieldName, fieldValue))
        return true;

    switch (tolower(fieldName[0])) {
        case '_':
            if ( fieldName % "_newLimit" ) { _newLimit = toUnsigned(fieldValue); return true; }
            break;
        default:
            break;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void QSetDailyLimit::finishParse() {
    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool QSetDailyLimit::Serialize(SFArchive& archive) {
    if (archive.isWriting())
        return ((const QSetDailyLimit*)this)->SerializeC(archive);

    CTransaction::Serialize(archive);

    archive >> _newLimit;
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool QSetDailyLimit::SerializeC(SFArchive& archive) const {
    CTransaction::SerializeC(archive);

    archive << _newLimit;

    return true;
}

//---------------------------------------------------------------------------
void QSetDailyLimit::registerClass(void) {
    static bool been_here = false;
    if (been_here) return;
    been_here = true;

    CTransaction::registerClass();

    uint32_t fieldNum = 1000;
    ADD_FIELD(QSetDailyLimit, "schema",  T_NUMBER, ++fieldNum);
    ADD_FIELD(QSetDailyLimit, "deleted", T_BOOL,  ++fieldNum);
    ADD_FIELD(QSetDailyLimit, "_newLimit", T_NUMBER, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(QSetDailyLimit, "schema");
    HIDE_FIELD(QSetDailyLimit, "deleted");

    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
SFString nextSetdailylimitChunk_custom(const SFString& fieldIn, const void *data) {
    const QSetDailyLimit *set = (const QSetDailyLimit *)data;
    if (set) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if ( fieldIn % "parsed" )
                    return nextBasenodeChunk(fieldIn, set);
                break;

            default:
                break;
        }
    }

    return "";
}

//---------------------------------------------------------------------------
bool QSetDailyLimit::handleCustomFormat(CExportContext& ctx, const SFString& fmtIn, void *data) const {
    // EXISTING_CODE
    // EXISTING_CODE
    return false;
}

//---------------------------------------------------------------------------
bool QSetDailyLimit::readBackLevel(SFArchive& archive) {
    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE

