/**
 * \file
 * \brief Wi-Fi
 *
 * \internal
 * \par modification history
 * - 1.00 17-06-23  phd, first implementation
 * \endinternal
 */
#ifndef __AW_WIFI_TYPES_H
#define __AW_WIFI_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif
#include "aw_bitops.h"
#define AW_WIFI_MAX_DEVICENAME_LEN          16
#define AW_WIFI_MAX_SSID_LEN                32
#define AW_WIFI_MAX_PASSPHRASE_LEN          64
#define AW_WIFI_ID_INVALID                  NULL
/**
 * Enumerated list of country codes
 */
#ifdef IL_BIGENDIAN
#define __MK_CNTRY(a, b, rev)  (((unsigned char)(b)) + (((unsigned char)(a))<<8) + (((unsigned short)(rev))<<16))
#else /* ifdef IL_BIGENDIAN */
#define __MK_CNTRY(a, b, rev)  (((unsigned char)(a)) + (((unsigned char)(b))<<8) + (((unsigned short)(rev))<<16))
#endif /* ifdef IL_BIGENDIAN */
typedef enum aw_wifi_country_code {
    AW_WIFI_COUNTRY_AFGHANISTAN                          = __MK_CNTRY('A', 'F', 0),             /* AF Afghanistan */
    AW_WIFI_COUNTRY_ALBANIA                              = __MK_CNTRY('A', 'L', 0),             /* AL Albania */
    AW_WIFI_COUNTRY_ALGERIA                              = __MK_CNTRY('D', 'Z', 0),             /* DZ Algeria */
    AW_WIFI_COUNTRY_AMERICAN_SAMOA                       = __MK_CNTRY('A', 'S', 0),             /* AS American_Samoa */
    AW_WIFI_COUNTRY_ANGOLA                               = __MK_CNTRY('A', 'O', 0),             /* AO Angola */
    AW_WIFI_COUNTRY_ANGUILLA                             = __MK_CNTRY('A', 'I', 0),             /* AI Anguilla */
    AW_WIFI_COUNTRY_ANTIGUA_AND_BARBUDA                  = __MK_CNTRY('A', 'G', 0),             /* AG Antigua_and_Barbuda */
    AW_WIFI_COUNTRY_ARGENTINA                            = __MK_CNTRY('A', 'R', 0),             /* AR Argentina */
    AW_WIFI_COUNTRY_ARMENIA                              = __MK_CNTRY('A', 'M', 0),             /* AM Armenia */
    AW_WIFI_COUNTRY_ARUBA                                = __MK_CNTRY('A', 'W', 0),             /* AW Aruba */
    AW_WIFI_COUNTRY_AUSTRALIA                            = __MK_CNTRY('A', 'U', 0),             /* AU Australia */
    AW_WIFI_COUNTRY_AUSTRIA                              = __MK_CNTRY('A', 'T', 0),             /* AT Austria */
    AW_WIFI_COUNTRY_AZERBAIJAN                           = __MK_CNTRY('A', 'Z', 0),             /* AZ Azerbaijan */
    AW_WIFI_COUNTRY_BAHAMAS                              = __MK_CNTRY('B', 'S', 0),             /* BS Bahamas */
    AW_WIFI_COUNTRY_BAHRAIN                              = __MK_CNTRY('B', 'H', 0),             /* BH Bahrain */
    AW_WIFI_COUNTRY_BAKER_ISLAND                         = __MK_CNTRY('0', 'B', 0),             /* 0B Baker_Island */
    AW_WIFI_COUNTRY_BANGLADESH                           = __MK_CNTRY('B', 'D', 0),             /* BD Bangladesh */
    AW_WIFI_COUNTRY_BARBADOS                             = __MK_CNTRY('B', 'B', 0),             /* BB Barbados */
    AW_WIFI_COUNTRY_BELARUS                              = __MK_CNTRY('B', 'Y', 0),             /* BY Belarus */
    AW_WIFI_COUNTRY_BELGIUM                              = __MK_CNTRY('B', 'E', 0),             /* BE Belgium */
    AW_WIFI_COUNTRY_BELIZE                               = __MK_CNTRY('B', 'Z', 0),             /* BZ Belize */
    AW_WIFI_COUNTRY_BENIN                                = __MK_CNTRY('B', 'J', 0),             /* BJ Benin */
    AW_WIFI_COUNTRY_BERMUDA                              = __MK_CNTRY('B', 'M', 0),             /* BM Bermuda */
    AW_WIFI_COUNTRY_BHUTAN                               = __MK_CNTRY('B', 'T', 0),             /* BT Bhutan */
    AW_WIFI_COUNTRY_BOLIVIA                              = __MK_CNTRY('B', 'O', 0),             /* BO Bolivia */
    AW_WIFI_COUNTRY_BOSNIA_AND_HERZEGOVINA               = __MK_CNTRY('B', 'A', 0),             /* BA Bosnia_and_Herzegovina */
    AW_WIFI_COUNTRY_BOTSWANA                             = __MK_CNTRY('B', 'W', 0),             /* BW Botswana */
    AW_WIFI_COUNTRY_BRAZIL                               = __MK_CNTRY('B', 'R', 0),             /* BR Brazil */
    AW_WIFI_COUNTRY_BRITISH_INDIAN_OCEAN_TERRITORY       = __MK_CNTRY('I', 'O', 0),             /* IO British_Indian_Ocean_Territory */
    AW_WIFI_COUNTRY_BRUNEI_DARUSSALAM                    = __MK_CNTRY('B', 'N', 0),             /* BN Brunei_Darussalam */
    AW_WIFI_COUNTRY_BULGARIA                             = __MK_CNTRY('B', 'G', 0),             /* BG Bulgaria */
    AW_WIFI_COUNTRY_BURKINA_FASO                         = __MK_CNTRY('B', 'F', 0),             /* BF Burkina_Faso */
    AW_WIFI_COUNTRY_BURUNDI                              = __MK_CNTRY('B', 'I', 0),             /* BI Burundi */
    AW_WIFI_COUNTRY_CAMBODIA                             = __MK_CNTRY('K', 'H', 0),             /* KH Cambodia */
    AW_WIFI_COUNTRY_CAMEROON                             = __MK_CNTRY('C', 'M', 0),             /* CM Cameroon */
    AW_WIFI_COUNTRY_CANADA                               = __MK_CNTRY('C', 'A', 0),             /* CA Canada */
    AW_WIFI_COUNTRY_CANADA_REV950                        = __MK_CNTRY('C', 'A', 950),           /* CA Canada Revision 950 */
    AW_WIFI_COUNTRY_CAPE_VERDE                           = __MK_CNTRY('C', 'V', 0),             /* CV Cape_Verde */
    AW_WIFI_COUNTRY_CAYMAN_ISLANDS                       = __MK_CNTRY('K', 'Y', 0),             /* KY Cayman_Islands */
    AW_WIFI_COUNTRY_CENTRAL_AFRICAN_REPUBLIC             = __MK_CNTRY('C', 'F', 0),             /* CF Central_African_Republic */
    AW_WIFI_COUNTRY_CHAD                                 = __MK_CNTRY('T', 'D', 0),             /* TD Chad */
    AW_WIFI_COUNTRY_CHILE                                = __MK_CNTRY('C', 'L', 0),             /* CL Chile */
    AW_WIFI_COUNTRY_CHINA                                = __MK_CNTRY('C', 'N', 0),             /* CN China */
    AW_WIFI_COUNTRY_CHRISTMAS_ISLAND                     = __MK_CNTRY('C', 'X', 0),             /* CX Christmas_Island */
    AW_WIFI_COUNTRY_COLOMBIA                             = __MK_CNTRY('C', 'O', 0),             /* CO Colombia */
    AW_WIFI_COUNTRY_COMOROS                              = __MK_CNTRY('K', 'M', 0),             /* KM Comoros */
    AW_WIFI_COUNTRY_CONGO                                = __MK_CNTRY('C', 'G', 0),             /* CG Congo */
    AW_WIFI_COUNTRY_CONGO_THE_DEMOCRATIC_REPUBLIC_OF_THE = __MK_CNTRY('C', 'D', 0),             /* CD Congo,_The_Democratic_Republic_Of_The */
    AW_WIFI_COUNTRY_COSTA_RICA                           = __MK_CNTRY('C', 'R', 0),             /* CR Costa_Rica */
    AW_WIFI_COUNTRY_COTE_DIVOIRE                         = __MK_CNTRY('C', 'I', 0),             /* CI Cote_D'ivoire */
    AW_WIFI_COUNTRY_CROATIA                              = __MK_CNTRY('H', 'R', 0),             /* HR Croatia */
    AW_WIFI_COUNTRY_CUBA                                 = __MK_CNTRY('C', 'U', 0),             /* CU Cuba */
    AW_WIFI_COUNTRY_CYPRUS                               = __MK_CNTRY('C', 'Y', 0),             /* CY Cyprus */
    AW_WIFI_COUNTRY_CZECH_REPUBLIC                       = __MK_CNTRY('C', 'Z', 0),             /* CZ Czech_Republic */
    AW_WIFI_COUNTRY_DENMARK                              = __MK_CNTRY('D', 'K', 0),             /* DK Denmark */
    AW_WIFI_COUNTRY_DJIBOUTI                             = __MK_CNTRY('D', 'J', 0),             /* DJ Djibouti */
    AW_WIFI_COUNTRY_DOMINICA                             = __MK_CNTRY('D', 'M', 0),             /* DM Dominica */
    AW_WIFI_COUNTRY_DOMINICAN_REPUBLIC                   = __MK_CNTRY('D', 'O', 0),             /* DO Dominican_Republic */
    AW_WIFI_COUNTRY_DOWN_UNDER                           = __MK_CNTRY('A', 'U', 0),             /* AU G'Day mate! */
    AW_WIFI_COUNTRY_ECUADOR                              = __MK_CNTRY('E', 'C', 0),             /* EC Ecuador */
    AW_WIFI_COUNTRY_EGYPT                                = __MK_CNTRY('E', 'G', 0),             /* EG Egypt */
    AW_WIFI_COUNTRY_EL_SALVADOR                          = __MK_CNTRY('S', 'V', 0),             /* SV El_Salvador */
    AW_WIFI_COUNTRY_EQUATORIAL_GUINEA                    = __MK_CNTRY('G', 'Q', 0),             /* GQ Equatorial_Guinea */
    AW_WIFI_COUNTRY_ERITREA                              = __MK_CNTRY('E', 'R', 0),             /* ER Eritrea */
    AW_WIFI_COUNTRY_ESTONIA                              = __MK_CNTRY('E', 'E', 0),             /* EE Estonia */
    AW_WIFI_COUNTRY_ETHIOPIA                             = __MK_CNTRY('E', 'T', 0),             /* ET Ethiopia */
    AW_WIFI_COUNTRY_FALKLAND_ISLANDS_MALVINAS            = __MK_CNTRY('F', 'K', 0),             /* FK Falkland_Islands_(Malvinas) */
    AW_WIFI_COUNTRY_FAROE_ISLANDS                        = __MK_CNTRY('F', 'O', 0),             /* FO Faroe_Islands */
    AW_WIFI_COUNTRY_FIJI                                 = __MK_CNTRY('F', 'J', 0),             /* FJ Fiji */
    AW_WIFI_COUNTRY_FINLAND                              = __MK_CNTRY('F', 'I', 0),             /* FI Finland */
    AW_WIFI_COUNTRY_FRANCE                               = __MK_CNTRY('F', 'R', 0),             /* FR France */
    AW_WIFI_COUNTRY_FRENCH_GUINA                         = __MK_CNTRY('G', 'F', 0),             /* GF French_Guina */
    AW_WIFI_COUNTRY_FRENCH_POLYNESIA                     = __MK_CNTRY('P', 'F', 0),             /* PF French_Polynesia */
    AW_WIFI_COUNTRY_FRENCH_SOUTHERN_TERRITORIES          = __MK_CNTRY('T', 'F', 0),             /* TF French_Southern_Territories */
    AW_WIFI_COUNTRY_GABON                                = __MK_CNTRY('G', 'A', 0),             /* GA Gabon */
    AW_WIFI_COUNTRY_GAMBIA                               = __MK_CNTRY('G', 'M', 0),             /* GM Gambia */
    AW_WIFI_COUNTRY_GEORGIA                              = __MK_CNTRY('G', 'E', 0),             /* GE Georgia */
    AW_WIFI_COUNTRY_GERMANY                              = __MK_CNTRY('D', 'E', 0),             /* DE Germany */
    AW_WIFI_COUNTRY_EUROPEAN_WIDE_REV895                 = __MK_CNTRY('E', '0', 895),           /* E0 European_Wide Revision 895 */
    AW_WIFI_COUNTRY_GHANA                                = __MK_CNTRY('G', 'H', 0),             /* GH Ghana */
    AW_WIFI_COUNTRY_GIBRALTAR                            = __MK_CNTRY('G', 'I', 0),             /* GI Gibraltar */
    AW_WIFI_COUNTRY_GREECE                               = __MK_CNTRY('G', 'R', 0),             /* GR Greece */
    AW_WIFI_COUNTRY_GRENADA                              = __MK_CNTRY('G', 'D', 0),             /* GD Grenada */
    AW_WIFI_COUNTRY_GUADELOUPE                           = __MK_CNTRY('G', 'P', 0),             /* GP Guadeloupe */
    AW_WIFI_COUNTRY_GUAM                                 = __MK_CNTRY('G', 'U', 0),             /* GU Guam */
    AW_WIFI_COUNTRY_GUATEMALA                            = __MK_CNTRY('G', 'T', 0),             /* GT Guatemala */
    AW_WIFI_COUNTRY_GUERNSEY                             = __MK_CNTRY('G', 'G', 0),             /* GG Guernsey */
    AW_WIFI_COUNTRY_GUINEA                               = __MK_CNTRY('G', 'N', 0),             /* GN Guinea */
    AW_WIFI_COUNTRY_GUINEA_BISSAU                        = __MK_CNTRY('G', 'W', 0),             /* GW Guinea-bissau */
    AW_WIFI_COUNTRY_GUYANA                               = __MK_CNTRY('G', 'Y', 0),             /* GY Guyana */
    AW_WIFI_COUNTRY_HAITI                                = __MK_CNTRY('H', 'T', 0),             /* HT Haiti */
    AW_WIFI_COUNTRY_HOLY_SEE_VATICAN_CITY_STATE          = __MK_CNTRY('V', 'A', 0),             /* VA Holy_See_(Vatican_City_State) */
    AW_WIFI_COUNTRY_HONDURAS                             = __MK_CNTRY('H', 'N', 0),             /* HN Honduras */
    AW_WIFI_COUNTRY_HONG_KONG                            = __MK_CNTRY('H', 'K', 0),             /* HK Hong_Kong */
    AW_WIFI_COUNTRY_HUNGARY                              = __MK_CNTRY('H', 'U', 0),             /* HU Hungary */
    AW_WIFI_COUNTRY_ICELAND                              = __MK_CNTRY('I', 'S', 0),             /* IS Iceland */
    AW_WIFI_COUNTRY_INDIA                                = __MK_CNTRY('I', 'N', 0),             /* IN India */
    AW_WIFI_COUNTRY_INDONESIA                            = __MK_CNTRY('I', 'D', 0),             /* ID Indonesia */
    AW_WIFI_COUNTRY_IRAN_ISLAMIC_REPUBLIC_OF             = __MK_CNTRY('I', 'R', 0),             /* IR Iran,_Islamic_Republic_Of */
    AW_WIFI_COUNTRY_IRAQ                                 = __MK_CNTRY('I', 'Q', 0),             /* IQ Iraq */
    AW_WIFI_COUNTRY_IRELAND                              = __MK_CNTRY('I', 'E', 0),             /* IE Ireland */
    AW_WIFI_COUNTRY_ISRAEL                               = __MK_CNTRY('I', 'L', 0),             /* IL Israel */
    AW_WIFI_COUNTRY_ITALY                                = __MK_CNTRY('I', 'T', 0),             /* IT Italy */
    AW_WIFI_COUNTRY_JAMAICA                              = __MK_CNTRY('J', 'M', 0),             /* JM Jamaica */
    AW_WIFI_COUNTRY_JAPAN                                = __MK_CNTRY('J', 'P', 0),             /* JP Japan */
    AW_WIFI_COUNTRY_JERSEY                               = __MK_CNTRY('J', 'E', 0),             /* JE Jersey */
    AW_WIFI_COUNTRY_JORDAN                               = __MK_CNTRY('J', 'O', 0),             /* JO Jordan */
    AW_WIFI_COUNTRY_KAZAKHSTAN                           = __MK_CNTRY('K', 'Z', 0),             /* KZ Kazakhstan */
    AW_WIFI_COUNTRY_KENYA                                = __MK_CNTRY('K', 'E', 0),             /* KE Kenya */
    AW_WIFI_COUNTRY_KIRIBATI                             = __MK_CNTRY('K', 'I', 0),             /* KI Kiribati */
    AW_WIFI_COUNTRY_KOREA_REPUBLIC_OF                    = __MK_CNTRY('K', 'R', 1),             /* KR Korea,_Republic_Of */
    AW_WIFI_COUNTRY_KOSOVO                               = __MK_CNTRY('0', 'A', 0),             /* 0A Kosovo */
    AW_WIFI_COUNTRY_KUWAIT                               = __MK_CNTRY('K', 'W', 0),             /* KW Kuwait */
    AW_WIFI_COUNTRY_KYRGYZSTAN                           = __MK_CNTRY('K', 'G', 0),             /* KG Kyrgyzstan */
    AW_WIFI_COUNTRY_LAO_PEOPLES_DEMOCRATIC_REPUBIC       = __MK_CNTRY('L', 'A', 0),             /* LA Lao_People's_Democratic_Repubic */
    AW_WIFI_COUNTRY_LATVIA                               = __MK_CNTRY('L', 'V', 0),             /* LV Latvia */
    AW_WIFI_COUNTRY_LEBANON                              = __MK_CNTRY('L', 'B', 0),             /* LB Lebanon */
    AW_WIFI_COUNTRY_LESOTHO                              = __MK_CNTRY('L', 'S', 0),             /* LS Lesotho */
    AW_WIFI_COUNTRY_LIBERIA                              = __MK_CNTRY('L', 'R', 0),             /* LR Liberia */
    AW_WIFI_COUNTRY_LIBYAN_ARAB_JAMAHIRIYA               = __MK_CNTRY('L', 'Y', 0),             /* LY Libyan_Arab_Jamahiriya */
    AW_WIFI_COUNTRY_LIECHTENSTEIN                        = __MK_CNTRY('L', 'I', 0),             /* LI Liechtenstein */
    AW_WIFI_COUNTRY_LITHUANIA                            = __MK_CNTRY('L', 'T', 0),             /* LT Lithuania */
    AW_WIFI_COUNTRY_LUXEMBOURG                           = __MK_CNTRY('L', 'U', 0),             /* LU Luxembourg */
    AW_WIFI_COUNTRY_MACAO                                = __MK_CNTRY('M', 'O', 0),             /* MO Macao */
    AW_WIFI_COUNTRY_MACEDONIA_FORMER_YUGOSLAV_REPUBLIC_OF= __MK_CNTRY('M', 'K', 0),             /* MK Macedonia,_Former_Yugoslav_Republic_Of */
    AW_WIFI_COUNTRY_MADAGASCAR                           = __MK_CNTRY('M', 'G', 0),             /* MG Madagascar */
    AW_WIFI_COUNTRY_MALAWI                               = __MK_CNTRY('M', 'W', 0),             /* MW Malawi */
    AW_WIFI_COUNTRY_MALAYSIA                             = __MK_CNTRY('M', 'Y', 0),             /* MY Malaysia */
    AW_WIFI_COUNTRY_MALDIVES                             = __MK_CNTRY('M', 'V', 0),             /* MV Maldives */
    AW_WIFI_COUNTRY_MALI                                 = __MK_CNTRY('M', 'L', 0),             /* ML Mali */
    AW_WIFI_COUNTRY_MALTA                                = __MK_CNTRY('M', 'T', 0),             /* MT Malta */
    AW_WIFI_COUNTRY_MAN_ISLE_OF                          = __MK_CNTRY('I', 'M', 0),             /* IM Man,_Isle_Of */
    AW_WIFI_COUNTRY_MARTINIQUE                           = __MK_CNTRY('M', 'Q', 0),             /* MQ Martinique */
    AW_WIFI_COUNTRY_MAURITANIA                           = __MK_CNTRY('M', 'R', 0),             /* MR Mauritania */
    AW_WIFI_COUNTRY_MAURITIUS                            = __MK_CNTRY('M', 'U', 0),             /* MU Mauritius */
    AW_WIFI_COUNTRY_MAYOTTE                              = __MK_CNTRY('Y', 'T', 0),             /* YT Mayotte */
    AW_WIFI_COUNTRY_MEXICO                               = __MK_CNTRY('M', 'X', 0),             /* MX Mexico */
    AW_WIFI_COUNTRY_MICRONESIA_FEDERATED_STATES_OF       = __MK_CNTRY('F', 'M', 0),             /* FM Micronesia,_Federated_States_Of */
    AW_WIFI_COUNTRY_MOLDOVA_REPUBLIC_OF                  = __MK_CNTRY('M', 'D', 0),             /* MD Moldova,_Republic_Of */
    AW_WIFI_COUNTRY_MONACO                               = __MK_CNTRY('M', 'C', 0),             /* MC Monaco */
    AW_WIFI_COUNTRY_MONGOLIA                             = __MK_CNTRY('M', 'N', 0),             /* MN Mongolia */
    AW_WIFI_COUNTRY_MONTENEGRO                           = __MK_CNTRY('M', 'E', 0),             /* ME Montenegro */
    AW_WIFI_COUNTRY_MONTSERRAT                           = __MK_CNTRY('M', 'S', 0),             /* MS Montserrat */
    AW_WIFI_COUNTRY_MOROCCO                              = __MK_CNTRY('M', 'A', 0),             /* MA Morocco */
    AW_WIFI_COUNTRY_MOZAMBIQUE                           = __MK_CNTRY('M', 'Z', 0),             /* MZ Mozambique */
    AW_WIFI_COUNTRY_MYANMAR                              = __MK_CNTRY('M', 'M', 0),             /* MM Myanmar */
    AW_WIFI_COUNTRY_NAMIBIA                              = __MK_CNTRY('N', 'A', 0),             /* NA Namibia */
    AW_WIFI_COUNTRY_NAURU                                = __MK_CNTRY('N', 'R', 0),             /* NR Nauru */
    AW_WIFI_COUNTRY_NEPAL                                = __MK_CNTRY('N', 'P', 0),             /* NP Nepal */
    AW_WIFI_COUNTRY_NETHERLANDS                          = __MK_CNTRY('N', 'L', 0),             /* NL Netherlands */
    AW_WIFI_COUNTRY_NETHERLANDS_ANTILLES                 = __MK_CNTRY('A', 'N', 0),             /* AN Netherlands_Antilles */
    AW_WIFI_COUNTRY_NEW_CALEDONIA                        = __MK_CNTRY('N', 'C', 0),             /* NC New_Caledonia */
    AW_WIFI_COUNTRY_NEW_ZEALAND                          = __MK_CNTRY('N', 'Z', 0),             /* NZ New_Zealand */
    AW_WIFI_COUNTRY_NICARAGUA                            = __MK_CNTRY('N', 'I', 0),             /* NI Nicaragua */
    AW_WIFI_COUNTRY_NIGER                                = __MK_CNTRY('N', 'E', 0),             /* NE Niger */
    AW_WIFI_COUNTRY_NIGERIA                              = __MK_CNTRY('N', 'G', 0),             /* NG Nigeria */
    AW_WIFI_COUNTRY_NORFOLK_ISLAND                       = __MK_CNTRY('N', 'F', 0),             /* NF Norfolk_Island */
    AW_WIFI_COUNTRY_NORTHERN_MARIANA_ISLANDS             = __MK_CNTRY('M', 'P', 0),             /* MP Northern_Mariana_Islands */
    AW_WIFI_COUNTRY_NORWAY                               = __MK_CNTRY('N', 'O', 0),             /* NO Norway */
    AW_WIFI_COUNTRY_OMAN                                 = __MK_CNTRY('O', 'M', 0),             /* OM Oman */
    AW_WIFI_COUNTRY_PAKISTAN                             = __MK_CNTRY('P', 'K', 0),             /* PK Pakistan */
    AW_WIFI_COUNTRY_PALAU                                = __MK_CNTRY('P', 'W', 0),             /* PW Palau */
    AW_WIFI_COUNTRY_PANAMA                               = __MK_CNTRY('P', 'A', 0),             /* PA Panama */
    AW_WIFI_COUNTRY_PAPUA_NEW_GUINEA                     = __MK_CNTRY('P', 'G', 0),             /* PG Papua_New_Guinea */
    AW_WIFI_COUNTRY_PARAGUAY                             = __MK_CNTRY('P', 'Y', 0),             /* PY Paraguay */
    AW_WIFI_COUNTRY_PERU                                 = __MK_CNTRY('P', 'E', 0),             /* PE Peru */
    AW_WIFI_COUNTRY_PHILIPPINES                          = __MK_CNTRY('P', 'H', 0),             /* PH Philippines */
    AW_WIFI_COUNTRY_POLAND                               = __MK_CNTRY('P', 'L', 0),             /* PL Poland */
    AW_WIFI_COUNTRY_PORTUGAL                             = __MK_CNTRY('P', 'T', 0),             /* PT Portugal */
    AW_WIFI_COUNTRY_PUETO_RICO                           = __MK_CNTRY('P', 'R', 0),             /* PR Pueto_Rico */
    AW_WIFI_COUNTRY_QATAR                                = __MK_CNTRY('Q', 'A', 0),             /* QA Qatar */
    AW_WIFI_COUNTRY_REUNION                              = __MK_CNTRY('R', 'E', 0),             /* RE Reunion */
    AW_WIFI_COUNTRY_ROMANIA                              = __MK_CNTRY('R', 'O', 0),             /* RO Romania */
    AW_WIFI_COUNTRY_RUSSIAN_FEDERATION                   = __MK_CNTRY('R', 'U', 0),             /* RU Russian_Federation */
    AW_WIFI_COUNTRY_RWANDA                               = __MK_CNTRY('R', 'W', 0),             /* RW Rwanda */
    AW_WIFI_COUNTRY_SAINT_KITTS_AND_NEVIS                = __MK_CNTRY('K', 'N', 0),             /* KN Saint_Kitts_and_Nevis */
    AW_WIFI_COUNTRY_SAINT_LUCIA                          = __MK_CNTRY('L', 'C', 0),             /* LC Saint_Lucia */
    AW_WIFI_COUNTRY_SAINT_PIERRE_AND_MIQUELON            = __MK_CNTRY('P', 'M', 0),             /* PM Saint_Pierre_and_Miquelon */
    AW_WIFI_COUNTRY_SAINT_VINCENT_AND_THE_GRENADINES     = __MK_CNTRY('V', 'C', 0),             /* VC Saint_Vincent_and_The_Grenadines */
    AW_WIFI_COUNTRY_SAMOA                                = __MK_CNTRY('W', 'S', 0),             /* WS Samoa */
    AW_WIFI_COUNTRY_SANIT_MARTIN_SINT_MARTEEN            = __MK_CNTRY('M', 'F', 0),             /* MF Sanit_Martin_/_Sint_Marteen */
    AW_WIFI_COUNTRY_SAO_TOME_AND_PRINCIPE                = __MK_CNTRY('S', 'T', 0),             /* ST Sao_Tome_and_Principe */
    AW_WIFI_COUNTRY_SAUDI_ARABIA                         = __MK_CNTRY('S', 'A', 0),             /* SA Saudi_Arabia */
    AW_WIFI_COUNTRY_SENEGAL                              = __MK_CNTRY('S', 'N', 0),             /* SN Senegal */
    AW_WIFI_COUNTRY_SERBIA                               = __MK_CNTRY('R', 'S', 0),             /* RS Serbia */
    AW_WIFI_COUNTRY_SEYCHELLES                           = __MK_CNTRY('S', 'C', 0),             /* SC Seychelles */
    AW_WIFI_COUNTRY_SIERRA_LEONE                         = __MK_CNTRY('S', 'L', 0),             /* SL Sierra_Leone */
    AW_WIFI_COUNTRY_SINGAPORE                            = __MK_CNTRY('S', 'G', 0),             /* SG Singapore */
    AW_WIFI_COUNTRY_SLOVAKIA                             = __MK_CNTRY('S', 'K', 0),             /* SK Slovakia */
    AW_WIFI_COUNTRY_SLOVENIA                             = __MK_CNTRY('S', 'I', 0),             /* SI Slovenia */
    AW_WIFI_COUNTRY_SOLOMON_ISLANDS                      = __MK_CNTRY('S', 'B', 0),             /* SB Solomon_Islands */
    AW_WIFI_COUNTRY_SOMALIA                              = __MK_CNTRY('S', 'O', 0),             /* SO Somalia */
    AW_WIFI_COUNTRY_SOUTH_AFRICA                         = __MK_CNTRY('Z', 'A', 0),             /* ZA South_Africa */
    AW_WIFI_COUNTRY_SPAIN                                = __MK_CNTRY('E', 'S', 0),             /* ES Spain */
    AW_WIFI_COUNTRY_SRI_LANKA                            = __MK_CNTRY('L', 'K', 0),             /* LK Sri_Lanka */
    AW_WIFI_COUNTRY_SURINAME                             = __MK_CNTRY('S', 'R', 0),             /* SR Suriname */
    AW_WIFI_COUNTRY_SWAZILAND                            = __MK_CNTRY('S', 'Z', 0),             /* SZ Swaziland */
    AW_WIFI_COUNTRY_SWEDEN                               = __MK_CNTRY('S', 'E', 0),             /* SE Sweden */
    AW_WIFI_COUNTRY_SWITZERLAND                          = __MK_CNTRY('C', 'H', 0),             /* CH Switzerland */
    AW_WIFI_COUNTRY_SYRIAN_ARAB_REPUBLIC                 = __MK_CNTRY('S', 'Y', 0),             /* SY Syrian_Arab_Republic */
    AW_WIFI_COUNTRY_TAIWAN_PROVINCE_OF_CHINA             = __MK_CNTRY('T', 'W', 0),             /* TW Taiwan,_Province_Of_China */
    AW_WIFI_COUNTRY_TAJIKISTAN                           = __MK_CNTRY('T', 'J', 0),             /* TJ Tajikistan */
    AW_WIFI_COUNTRY_TANZANIA_UNITED_REPUBLIC_OF          = __MK_CNTRY('T', 'Z', 0),             /* TZ Tanzania,_United_Republic_Of */
    AW_WIFI_COUNTRY_THAILAND                             = __MK_CNTRY('T', 'H', 0),             /* TH Thailand */
    AW_WIFI_COUNTRY_TOGO                                 = __MK_CNTRY('T', 'G', 0),             /* TG Togo */
    AW_WIFI_COUNTRY_TONGA                                = __MK_CNTRY('T', 'O', 0),             /* TO Tonga */
    AW_WIFI_COUNTRY_TRINIDAD_AND_TOBAGO                  = __MK_CNTRY('T', 'T', 0),             /* TT Trinidad_and_Tobago */
    AW_WIFI_COUNTRY_TUNISIA                              = __MK_CNTRY('T', 'N', 0),             /* TN Tunisia */
    AW_WIFI_COUNTRY_TURKEY                               = __MK_CNTRY('T', 'R', 0),             /* TR Turkey */
    AW_WIFI_COUNTRY_TURKMENISTAN                         = __MK_CNTRY('T', 'M', 0),             /* TM Turkmenistan */
    AW_WIFI_COUNTRY_TURKS_AND_CAICOS_ISLANDS             = __MK_CNTRY('T', 'C', 0),             /* TC Turks_and_Caicos_Islands */
    AW_WIFI_COUNTRY_TUVALU                               = __MK_CNTRY('T', 'V', 0),             /* TV Tuvalu */
    AW_WIFI_COUNTRY_UGANDA                               = __MK_CNTRY('U', 'G', 0),             /* UG Uganda */
    AW_WIFI_COUNTRY_UKRAINE                              = __MK_CNTRY('U', 'A', 0),             /* UA Ukraine */
    AW_WIFI_COUNTRY_UNITED_ARAB_EMIRATES                 = __MK_CNTRY('A', 'E', 0),             /* AE United_Arab_Emirates */
    AW_WIFI_COUNTRY_UNITED_KINGDOM                       = __MK_CNTRY('G', 'B', 0),             /* GB United_Kingdom */
    AW_WIFI_COUNTRY_UNITED_STATES                        = __MK_CNTRY('U', 'S', 0),             /* US United_States */
    AW_WIFI_COUNTRY_UNITED_STATES_REV4                   = __MK_CNTRY('U', 'S', 4),             /* US United_States Revision 4 */
    AW_WIFI_COUNTRY_UNITED_STATES_REV931                 = __MK_CNTRY('Q', '1', 931),           /* Q1 United_States Revision 931 */
    AW_WIFI_COUNTRY_UNITED_STATES_NO_DFS                 = __MK_CNTRY('Q', '2', 0),             /* Q2 United_States_(No_DFS) */
    AW_WIFI_COUNTRY_UNITED_STATES_MINOR_OUTLYING_ISLANDS = __MK_CNTRY('U', 'M', 0),             /* UM United_States_Minor_Outlying_Islands */
    AW_WIFI_COUNTRY_URUGUAY                              = __MK_CNTRY('U', 'Y', 0),             /* UY Uruguay */
    AW_WIFI_COUNTRY_UZBEKISTAN                           = __MK_CNTRY('U', 'Z', 0),             /* UZ Uzbekistan */
    AW_WIFI_COUNTRY_VANUATU                              = __MK_CNTRY('V', 'U', 0),             /* VU Vanuatu */
    AW_WIFI_COUNTRY_VENEZUELA                            = __MK_CNTRY('V', 'E', 0),             /* VE Venezuela */
    AW_WIFI_COUNTRY_VIET_NAM                             = __MK_CNTRY('V', 'N', 0),             /* VN Viet_Nam */
    AW_WIFI_COUNTRY_VIRGIN_ISLANDS_BRITISH               = __MK_CNTRY('V', 'G', 0),             /* VG Virgin_Islands,_British */
    AW_WIFI_COUNTRY_VIRGIN_ISLANDS_US                    = __MK_CNTRY('V', 'I', 0),             /* VI Virgin_Islands,_U.S. */
    AW_WIFI_COUNTRY_WALLIS_AND_FUTUNA                    = __MK_CNTRY('W', 'F', 0),             /* WF Wallis_and_Futuna */
    AW_WIFI_COUNTRY_WEST_BANK                            = __MK_CNTRY('0', 'C', 0),             /* 0C West_Bank */
    AW_WIFI_COUNTRY_WESTERN_SAHARA                       = __MK_CNTRY('E', 'H', 0),             /* EH Western_Sahara */
    AW_WIFI_COUNTRY_WORLD_WIDE_XV_REV983                 = __MK_CNTRY('X', 'V', 983),           /* Worldwide Locale Revision 983 */
    AW_WIFI_COUNTRY_WORLD_WIDE_XX                        = __MK_CNTRY('X', 'X', 0),             /* Worldwide Locale (passive Ch12-14) */
    AW_WIFI_COUNTRY_WORLD_WIDE_XX_REV17                  = __MK_CNTRY('X', 'X', 17),            /* Worldwide Locale (passive Ch12-14) Revision 17 */
    AW_WIFI_COUNTRY_YEMEN                                = __MK_CNTRY('Y', 'E', 0),             /* YE Yemen */
    AW_WIFI_COUNTRY_ZAMBIA                               = __MK_CNTRY('Z', 'M', 0),             /* ZM Zambia */
    AW_WIFI_COUNTRY_ZIMBABWE                             = __MK_CNTRY('Z', 'W', 0),             /* ZW Zimbabwe */
} aw_wifi_country_code_t;
#undef __MK_CNTRY
/**
 * \brief Enumeration of work modes
 */
typedef enum aw_wifi_opmode {
    AW_WIFI_MODE_STOP           = 0,
    AW_WIFI_MODE_STA_ONLY       = AW_BIT(0),
    AW_WIFI_MODE_AP_ONLY        = AW_BIT(1),
    AW_WIFI_MODE_APSTA          = (AW_WIFI_MODE_STA_ONLY | AW_WIFI_MODE_AP_ONLY),
    AW_WIFI_MODE_FORCE_16_BIT   = 0x7fff
} aw_wifi_opmode_t;
/**
 * \brief Enumeration of run status
 */
typedef enum aw_wifi_state {
    AW_WIFI_STATE_UNAVALIABLE   = 0,
    AW_WIFI_STATE_EXIST         = AW_BIT(0),      /* exist or not exist */
    AW_WIFI_STATE_POWER         = AW_BIT(1),      /* power on or off */
    AW_WIFI_STATE_UP            = AW_BIT(2),      /* device core is up or not */
    AW_WIFI_STATE_AP_ON         = AW_BIT(3),      /* soft ap is on */
    AW_WIFI_STATE_STA_JOINED    = AW_BIT(4),      /* sta is joined */
    AW_WIFI_STATE_FUNCTIONAL    = (AW_WIFI_STATE_EXIST | AW_WIFI_STATE_POWER | AW_WIFI_STATE_UP),
    AW_WIFI_STATE_FORCE_16_BIT  = 0x7fff
} aw_wifi_state_t;
/**
 * \brief Enumeration of network types
 */
typedef enum aw_wifi_bss_type {
    AW_WIFI_BSS_TYPE_INFRASTRUCTURE =  0,       /**< Denotes infrastructure network                  */
    AW_WIFI_BSS_TYPE_ADHOC          =  1,       /**< Denotes an 802.11 ad-hoc IBSS network           */
    AW_WIFI_BSS_TYPE_ANY            =  2,       /**< Denotes either infrastructure or ad-hoc network */
    AW_WIFI_BSS_TYPE_UNKNOWN        = -1        /**< May be returned by scan function if BSS type is unknown.
                                                Do not pass this to the Join function            */
} aw_wifi_bss_type_t;
/**
 * \brief Enumeration of 802.11 radio bands
 */
typedef enum aw_802_11_band {
    AW_WIFI_802_11_BAND_5GHZ   = 0,              /**< Denotes 5GHz radio band   */
    AW_WIFI_802_11_BAND_2_4GHZ = 1               /**< Denotes 2.4GHz radio band */
} aw_wifi_802_11_band_t;
/**
 * \brief Service Set Identifier (i.e. Name of Access Point)
 */
typedef struct aw_wifi_ssid {
    uint8_t length;                         /**< SSID length */
    uint8_t pad0[3];                        /**< Padding */
    uint8_t value[AW_WIFI_MAX_SSID_LEN];    /**< SSID name (AP name)  */
} aw_wifi_ssid_t;
/**
 * \brief Pre-Share Key or PMK (i.e. Password of Access Point)
 * If the length is 64, the password is regarded as PMK.
 */
typedef struct aw_wifi_key {
    uint8_t length;                             /**< key length */
    uint8_t pad0[3];                            /**< Padding */
    uint8_t value[AW_WIFI_MAX_PASSPHRASE_LEN];  /**< key content  */
} aw_wifi_key_t;
/**
 * \brief Enumeration of Wi-Fi security modes
 */
#ifdef __WEP_ENABLED
#undef __WEP_ENABLED
#endif
#ifdef __TKIP_ENABLED
#undef __TKIP_ENABLED
#endif
#ifdef __AES_ENABLED
#undef __AES_ENABLED
#endif
#ifdef __SHARED_ENABLED
#undef __SHARED_ENABLED
#endif
#ifdef __WPA_SECURITY
#undef __WPA_SECURITY
#endif
#ifdef __WPA2_SECURITY
#undef __WPA2_SECURITY
#endif
#ifdef __ENT_ENABLED
#undef __ENT_ENABLED
#endif
#ifdef __WPS_ENABLED
#undef __WPS_ENABLED
#endif
#ifdef __IBSS_ENABLED
#undef __IBSS_ENABLED
#endif
#define __WEP_ENABLED                 0x0001
#define __TKIP_ENABLED                0x0002
#define __AES_ENABLED                 0x0004
#define __SHARED_ENABLED          0x00008000
#define __WPA_SECURITY            0x00200000
#define __WPA2_SECURITY           0x00400000
#define __ENT_ENABLED             0x02000000
#define __WPS_ENABLED             0x10000000
#define __IBSS_ENABLED            0x20000000
typedef enum aw_wifi_security {
    AW_WIFI_SECURITY_OPEN           = 0,                                                                   /**< Open security                                         */
    AW_WIFI_SECURITY_WEP_PSK        = __WEP_ENABLED,                                                       /**< WEP PSK Security with open authentication             */
    AW_WIFI_SECURITY_WEP_SHARED     = (__WEP_ENABLED   | __SHARED_ENABLED),                                /**< WEP PSK Security with shared authentication           */
    AW_WIFI_SECURITY_WPA_TKIP_PSK   = (__WPA_SECURITY  | __TKIP_ENABLED),                                  /**< WPA PSK Security with TKIP                            */
    AW_WIFI_SECURITY_WPA_AES_PSK    = (__WPA_SECURITY  | __AES_ENABLED),                                   /**< WPA PSK Security with AES                             */
    AW_WIFI_SECURITY_WPA_MIXED_PSK  = (__WPA_SECURITY  | __AES_ENABLED | __TKIP_ENABLED),                  /**< WPA PSK Security with AES & TKIP                      */
    AW_WIFI_SECURITY_WPA2_AES_PSK   = (__WPA2_SECURITY | __AES_ENABLED),                                   /**< WPA2 PSK Security with AES                            */
    AW_WIFI_SECURITY_WPA2_TKIP_PSK  = (__WPA2_SECURITY | __TKIP_ENABLED),                                  /**< WPA2 PSK Security with TKIP                           */
    AW_WIFI_SECURITY_WPA2_MIXED_PSK = (__WPA2_SECURITY | __AES_ENABLED | __TKIP_ENABLED),                  /**< WPA2 PSK Security with AES & TKIP                     */
    AW_WIFI_SECURITY_WPA_TKIP_ENT   = (__ENT_ENABLED | __WPA_SECURITY  | __TKIP_ENABLED),                  /**< WPA Enterprise Security with TKIP                     */
    AW_WIFI_SECURITY_WPA_AES_ENT    = (__ENT_ENABLED | __WPA_SECURITY  | __AES_ENABLED),                   /**< WPA Enterprise Security with AES                      */
    AW_WIFI_SECURITY_WPA_MIXED_ENT  = (__ENT_ENABLED | __WPA_SECURITY  | __AES_ENABLED | __TKIP_ENABLED),  /**< WPA Enterprise Security with AES & TKIP               */
    AW_WIFI_SECURITY_WPA2_TKIP_ENT  = (__ENT_ENABLED | __WPA2_SECURITY | __TKIP_ENABLED),                  /**< WPA2 Enterprise Security with TKIP                    */
    AW_WIFI_SECURITY_WPA2_AES_ENT   = (__ENT_ENABLED | __WPA2_SECURITY | __AES_ENABLED),                   /**< WPA2 Enterprise Security with AES                     */
    AW_WIFI_SECURITY_WPA2_MIXED_ENT = (__ENT_ENABLED | __WPA2_SECURITY | __AES_ENABLED | __TKIP_ENABLED),  /**< WPA2 Enterprise Security with AES & TKIP              */
    AW_WIFI_SECURITY_IBSS_OPEN      = (__IBSS_ENABLED),                                                    /**< Open security on IBSS ad-hoc network                  */
    AW_WIFI_SECURITY_WPS_OPEN       = (__WPS_ENABLED),                                                     /**< WPS with open security                                */
    AW_WIFI_SECURITY_WPS_SECURE     = (__WPS_ENABLED | __AES_ENABLED),                                     /**< WPS with AES security                                 */
    AW_WIFI_SECURITY_UNKNOWN        = -1,                                                                  /**< May be returned by scan function if security is unknown. Do not pass this to the join function! */
    AW_WIFI_SECURITY_FORCE_32_BIT   = 0x7fffffff                                                           /**< Exists only to force wiced_security_t type to 32 bits */
} aw_wifi_security_t;
#ifdef __WEP_ENABLED
#undef __WEP_ENABLED
#endif
#ifdef __TKIP_ENABLED
#undef __TKIP_ENABLED
#endif
#ifdef __AES_ENABLED
#undef __AES_ENABLED
#endif
#ifdef __SHARED_ENABLED
#undef __SHARED_ENABLED
#endif
#ifdef __WPA_SECURITY
#undef __WPA_SECURITY
#endif
#ifdef __WPA2_SECURITY
#undef __WPA2_SECURITY
#endif
#ifdef __ENT_ENABLED
#undef __ENT_ENABLED
#endif
#ifdef __WPS_ENABLED
#undef __WPS_ENABLED
#endif
#ifdef __IBSS_ENABLED
#undef __IBSS_ENABLED
#endif
/**
 * \brief Wi-Fi Device Control Handle
 */
typedef void * aw_wifi_id_t;
/**
 * \brief Enumeration of Wi-Fi interfaces
 */
typedef enum aw_wifi_interface {
    AW_WIFI_STA_INTERFACE = 0,  /**< STA or Client Interface        */
    AW_WIFI_AP_INTERFACE  = 1,  /**< AP  Interface                  */
    AW_WIFI_INTERFACE_MAX,      /**< used for counting interfaces   */
} aw_wifi_interface_t;
/**
 * \brief Wi-Fi Media Access Control address
 */
typedef struct {
    uint8_t octet[6];
} aw_wifi_mac_t;
/**
 * \brief Wi-Fi configuration for initialization in STA mode.
 */
typedef struct aw_wifi_sta_config {
    aw_wifi_ssid_t     ssid;             /**< The SSID of the target AP. */
    aw_wifi_key_t      key;              /**< The password of the target AP. */
    uint8_t            bssid_present;    /**< The BSSID is present if it is set to 1. Otherwise, it is set to 0. */
    aw_wifi_mac_t      bssid;            /**< The MAC address of the target AP. */
    uint8_t            security_present; /**< The security is present if it is set to 1. Otherwise, it is set to 0. */
    aw_wifi_security_t security;         /**< The security type. */
    uint8_t            is_joined;        /**< The STA is assocated to an AP. */
} aw_wifi_sta_config_t;
/**
 * \brief Wi-Fi configuration for initialization in AP mode.
 */
typedef struct aw_wifi_ap_config {
    aw_wifi_ssid_t     ssid;                /**< The SSID of the AP. */
    aw_wifi_key_t      key;                 /**< The password of the AP. */
    aw_wifi_security_t security;            /**< The security type. */
    uint8_t            channel;             /**< The channel. */
    uint8_t            is_up;               /**< The AP is running. */
} aw_wifi_ap_config_t;
/**
 * \brief Wi-Fi configuration for initialization.
 */
typedef struct aw_wifi_config {
    aw_wifi_opmode_t     opmode;            /**< Current operation mode.*/
    aw_wifi_sta_config_t sta;               /**< The configurations for the STA. */
    aw_wifi_ap_config_t  ap;                /**< The configurations for the AP. */
} aw_wifi_config_t;
/**
 * \brief config status.
 */
typedef struct aw_wifi_status {
    aw_wifi_state_t  state;                 /**< run state */
    aw_wifi_opmode_t last_opmode;           /**< Last operation mode.*/
} aw_wifi_status_t;
/**
 * \brief AP information
 */
typedef struct aw_wifi_ap_info {
    aw_wifi_ssid_t        ssid;             /**< Service Set Identification (i.e. Name of Access Point)                    */
    aw_wifi_mac_t         bssid;            /**< Basic Service Set Identification (i.e. MAC address of Access Point)       */
    int16_t               signal_strength;  /**< Receive Signal Strength Indication in dBm. <-90=Very poor, >-30=Excellent */
    uint32_t              max_data_rate;    /**< Maximum data rate in kilobits/s                                           */
    aw_wifi_bss_type_t    bss_type;         /**< Network type                                                              */
    aw_wifi_security_t    security;         /**< Security type                                                             */
    uint8_t               channel;          /**< Radio channel that the AP beacon was received on                          */
    aw_wifi_802_11_band_t band;             /**< Radio band                                                                */
} aw_wifi_ap_info_t;
/**
 * \brief STA information
 */
typedef struct aw_wifi_sta_info {
    aw_wifi_mac_t   bssid;            /**< BSSID of STA */
    int             signal_strength;  /**< dbm */
} aw_wifi_sta_info_t;
/**
 * Structure for storing scan results
 */
typedef struct aw_wifi_scan_result {
    aw_wifi_ssid_t              ssid;             /**< Service Set Identification (i.e. Name of Access Point)                    */
    aw_wifi_mac_t               bssid;            /**< Basic Service Set Identification (i.e. MAC address of Access Point)       */
    int16_t                     signal_strength;  /**< Receive Signal Strength Indication in dBm. <-90=Very poor, >-30=Excellent */
    uint32_t                    max_data_rate;    /**< Maximum data rate in kilobits/s                                           */
    aw_wifi_bss_type_t          bss_type;         /**< Network type                                                              */
    aw_wifi_security_t          security;         /**< Security type                                                             */
    uint8_t                     channel;          /**< Radio channel that the AP beacon was received on                          */
    aw_wifi_802_11_band_t       band;             /**< Radio band                                                                */
    uint8_t                     ccode[4];         /**< Two letter ISO country code from AP                                       */
    uint8_t                     flags;            /**< flags                                                                     */
    struct aw_wifi_scan_result *next;             /**< Pointer to the next scan result                                           */
} aw_wifi_scan_result_t;
/**
 * Enumeration of methods of scanning
 */
typedef enum aw_wifi_scan_type {
    AW_WIFI_SCAN_TYPE_ACTIVE              = 0,  /**< Actively scan a network by sending 802.11 probe(s)         */
    AW_WIFI_SCAN_TYPE_PASSIVE            ,  /**< Passively scan a network by listening for beacons from APs */
    AW_WIFI_SCAN_TYPE_PNO                ,  /**< Use preferred network offload to detect an AP */
    AW_WIFI_SCAN_TYPE_PROHIBITED_CHANNELS   /**< Passively scan on channels not enabled by the country code */
} aw_wifi_scan_type_t;
typedef enum aw_wifi_scan_result_flag {
    AW_WIFI_SCAN_RESULT_FLAG_RSSI_OFF_CHANNEL   = 0x01,  /**< RSSI came from an off channel DSSS (1 or 1 Mb) Rx */
    AW_WIFI_SCAN_RESULT_FLAG_BEACON             = 0x02   /**< Beacon (vs probe response)                        */
} aw_wifi_scan_result_flag_t;
typedef enum aw_wifi_scan_status {
    AW_WIFI_SCAN_INCOMPLETE,
    AW_WIFI_SCAN_COMPLETED_SUCCESSFULLY,
    AW_WIFI_SCAN_ABORTED,
} aw_wifi_scan_status_t;
/**
 * Wi-Fi scan result
 */
typedef struct aw_wifi_scan_cb_result {
    aw_wifi_scan_result_t  ap_details;   /**< Access point details */
    void                  *p_arg;        /**< Pointer to user data passed into aw_wifi_scan() function */
} aw_wifi_scan_cb_result_t;
typedef aw_err_t (*aw_wifi_scan_callback_t) (aw_wifi_scan_cb_result_t *result,
                                             aw_wifi_scan_status_t     status);
typedef aw_err_t (*aw_wifi_get_sta_result_handler_t) (void               *p_arg,
                                                      aw_wifi_sta_info_t *p_info,
                                                      bool_t              b_complete);
/**
 * SoftAP events
 */
typedef enum aw_wifi_softap_event {
    AW_WIFI_AP_UNKNOWN_EVENT,         /**< Unknown SoftAP event       */
    AW_WIFI_AP_STA_JOINED_EVENT,      /**< a STA joined our SoftAP    */
    AW_WIFI_AP_STA_LEAVE_EVENT,       /**< a STA left our SoftAP      */
} aw_wifi_ap_event_t;
typedef void (*aw_wifi_ap_event_handler_t) (void                *p_arg,
                                            aw_wifi_ap_event_t   event,
                                            const aw_wifi_mac_t *mac_addr);
typedef void (*aw_wifi_raw_packet_processor_t) (void *p_arg, uint8_t *p_buf, size_t size);
#ifdef __cplusplus
}
#endif
#endif /* __AW_WIFI_TYPES_H */
/* end of file */