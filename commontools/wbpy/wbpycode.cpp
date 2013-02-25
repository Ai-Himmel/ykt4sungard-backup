//---------------------------------------------------------------------------



#include <windows.h>

#pragma htrstop

#include "wbpycode.h"

//#include <fstream>

#pragma argsused

/*

using namespace std;

static ofstream logfile("wplog.txt");

*/

// GBK „÷Јы±н

//{{{

const char HstrA [] = 

"яє пє аƒ пЌ ёя а» ц∞ нЅ а… ж» к” и® ис в÷ Џѕ р∆ џы" \

        "пІ ёо бн чц џк аї вЏ йб еџ съ ть ч° чй жЅ бЃ жс цЋ";



const char HstrB [] =

"б± фќ №Ў Ё√ ч… ц— е± кю ёг я¬ с£ с≠ Џж џа о” ф≤ дЇ" \

        "Ёт ўи жя м“ цµ р± Ёб сў хј Џй р« Џэ г£ н’ Ён сЎ чє"\

        "цЌ кЏ пЉ џќ џ– а‘ кі Ё© Ў∞ яЅ ею пх ў¬ ф∞ оѓ яў №к"\

        "бщ ой жЊ вЎ Ё… ец гє уў дд с‘ хѕ ул ж‘ уч ёµ е® ч¬"\

        "иµ ф≈ нЊ у÷ м‘ тщ цэ сє Ў“ н№ сџ џЌ вн гк №– з¬ м©"\

        "ч‘ жф с¶ пЏ м≠ мЃ пр жї с— чІ хњ ўѕ зЌ йƒ пў бў йл"\

        "лч ч∆ чё Џы ўч ёр вƒ а£ Ў√ ўс оа рЊ хџ нз хЋ ф§ лҐ"\

        "йё еЌ оя кќ х≥ я≤ о– к≥ зг е≤ рЏ";



const char HstrC [] = 

"ак не жо чх ф” и≤ Ўч а– до фљ у© №≥ вь бѓ дє аб иЊ в« п  в™ йґ йя с√" \

        "пп гв ж± оќ ў≠ т≤ ры ки жњ ео мш в№ дэ пв уЄ хр Џ∆ Ёџ ўж вг ес Ўц жљ Ё≈" \

        "г— цр №… бд жѕ к∆ гЃ л© вк џЋ вч мћ кЋ сй нЇ еш џе ё” и° аЅ еЈ Џ» н„ ц≥" \

        "йі Џя ия т… ох о™ Ў© и« џф ос сќ лу х® як тњ рЈ нч у„ аЌ ж  у§ чќ №Ё №ѓ" \

        "хЎ уш фщ сЁ б№ я≥ вЅ лЈ аі ў— с° вз №ы ф© гњ фЊ п• сђ ў± аь г∞ ц≈ йЋ џї" \

        "т№ хй и∆ иъ с“ Ў° вр з© гј чн ёх а® а№ хя зЁ л∞ ф≠ е„ вґ оЋ вл Џп йҐ й≥" \

        "тн Ёї р» х÷ к° цЇ яЏ мф №л рЋ фў №  и» жх иЃ д» зэ й® лн к£ бё йг вІ Ёэ" \

        "хЊ хн ўа";



const char HstrD [] = 

"я’ ё« а™ с„ жІ вт уќ ч∞ ч≤ бЈ я∞ з™ е  зй №§ чм нс сх йй рч ум ўў рг аҐ" \

        "Ёћ е£ с… Џ‘ џ  еі нЄ Ё– яґ вб лЃ фо пљ ав ф£ к≠ бЎ нг пл ф∆ а÷ пб ўб Ёґ кл" \

        "Ўµ ЏЃ џ° џж и№ н∆ чЊ жЈ Џ– й¶ ны нЏ а« бџ с≤ хЏ Џз џг зи од с∞ ф° хх цф оц" \

        "џм рђ №¶ ёй су лЇ хё цш Ўк за рџ сф фъ а§ лл н÷ оы яЋ бі л± рі џн бЉ лЋ лЎ" \

        "нѕ Ёъ уы тљ сЉ аљ д¬ иь лє чт ч« у∆ №ґ уЉ й≤ м— уэ н° н‘ н≠ пж нв нп хї гз" \

        "мј нї яЌ с÷ ом хв яб зґ гх Џа Ўй кж пҐ оЃ оъ вЇ ЎЉ";



const char HstrE [] =

"ен Ё≠ п∞ жє яј №√ йо џ— Џћ г’ гµ Ёа лс п… р  т¶ Ўђ цщ Ём ёф рє ц№ е« зн" \

        "оп ў¶ а≈ ян Џј";



const char HstrF [] = 

"џ“ нј б¶ ёђ м№ хм ёј о≤ иу Џъ и  о’ ц– ф≥ еъ з≥ мй тг ц≠ цо д« ли г≠ м≥" \

        "йЉ фд ух бф рт п– иы чч ў« цч еѓ гг нњ Ё„ џЇ яф ўЇ уЊ яї х√ фп пы х∆ ўм жЏ" \

        "№љ №ј вц з¶ з® №ё мр оЈ №т џЃ н… Ё≥ тґ ўл их ех Ё  тЁ б• тр нк ё‘ дж нл жв" \

        "ц÷ кз ту цы р• лґ бл";



const char HstrG [] = 

"кЄ ў§ о≈ жў жЎ ёќ Џл џт ка Ў§ кЃ џб гп №’ рб фы ёѕ дч йѕ я¶ кЇ нЈ з§ д∆" \

        "оЄ уа н∞ йј ЎЇ кљ з… й¬ ёї ЏЊ џђ пѓ џў жь сЋ Ў™ а√ №™ л° лх п” чј џЅ фі ті" \

        "н— яз Ў® фё ЁҐ вў ям зЃ цб л≈ тЉ ц° зо Ўю з√ уф чЄ бЄ иџ у— ЏЄ ж≈ м∞ е№ кн" \

        "йп р≥ Ё‘ тЅ хэ фю м± чљ гй Џђ кф оє о№ Ў≈ лы о≠ бƒ иф кц ру пј цс л“ рї я…" \

        "Ў‘ Џі ўƒ ч§ ёи д  о¬ рў яџ иж л„ бо ж£ рІ цў е≥ в— Ў– к– ую Ўџ кЅ чђ ўт зµ" \

        "нё цз я√ џц б∆ сш те аю ёв лљ ўе в£ й§ тд ин ЁЄ я»";



const char HstrH [] = 

"рј ою аЋ л№ х∞ сь тј чэ Џх кѕ м  Ё’ т• ёю еЂ зђ сю гм Ёп аг ёґ тЇ а∆ е©" \

        "кї р© тЂ е∞ Џ≠ ај џј к¬ оЅ тҐ гЎ фз џ÷ им зс ёњ ўк ё∞ г» гь Ё¶ ёЃ ўд ЏІ ръ" \

        "уу ф„ чњ бб еЋ №© ц„ тЃ м√ йх яь г± дп ас хъ в© мќ р… йќ х≠ м≤ д∞ зъ ўь б≤" \

        "вп мж мп уЋ ми р≠ р„ жи оь ил х„ вµ д° Ё» пћ еЊ зў чя џЉ дљ е’ дс цй яІ лЅ" \

        "Џт бе д“ еЎ дк иЂ ут с• у® ць Џґ я‘ т≥ кЌ зх чв гƒ дІ №о я№ дЂ №ц н£ ез ає" \

        "зј ё• у≥ г‘ в∆ Џї дг сл пЅ Ўе яЂ оЎ вЈ пм ал ёљ уґ нє ач";



//hstrI [] =



const char HstrJ [] =

"ЎҐ яі Ўј зб №Є нґ я“ Ўё яу ем у« пъ кч ке х“ з№ мі џ‘ оњ бІ Ўљ ў• у≈ кЂ"\

        "йк йЃ Ёр с§ ё™ т± ёб к™ б’ чд №Ѕ яв д© кй ў  фя х’ цЂ цЁ рҐ цк чў жч е» д§"\

        "ри у’ ф¬ Ёз х  пЎ бµ џ£ нҐ к© от тћ лќ рэ кІ Ё— д’" \

        "кщ ёц зћ Ёу цд рѕ чµ ао и≈ у» х¬ нъ с– пµ Џў кѓ фе еј ењ кр Џ… й• л¶ лм ў‘ хЁ"\

        "№ь фш з÷ нд ср дЃ з≠ кс фЁ №і жѓ №ъ т‘ х” ў’ цё р‘ ўЃ ёЎ р® лЄ би аЁ хі р№" \

        "аµ жЁ Џ¶ Џµ ё„ ио жЉ т° нў цЏ ф… тї чЇ оƒ сж с∆" \

        "Џб Ёј вџ вЋ й» и™ ж° Ё£ кб з∆ ко ад гю мЇ ЁЉ лж Џе Ўў л¬ ў” гљ ет е… л÷ жЇ в∞"\

        "мз еƒ рѓ фс гќ а± чЁ и— ик аў жё зе б» иц хы Ў  Ўг Џ№ в± ёІ й” пг хк џ« мя сд"\

        "уё че ё№ жщ џ» џ≤ №м";



const char HstrK [] = 

"т¬ я« Ўы лћ пі Ў№ џо вэ ош Ё№ п« вй ни кђ ў© Ё® гџ оЂ Ўш г  о÷ ек иа он"\

        "кы зж йр рв оЁ т§ пэ сљ оІ тт чЅ б≥ г° лі жм зЉ аЊ дџ пЊ сћ пђ ў≈ б« ун №“"\

        "яµ уЎ ёҐ ЎЏ №• чЉ зЂ аЈ ў® Ўб џ¶ яа бц лЏ ч≈ Џ≤ я—" \

        "Џњ ё≈ Џч џџ жю к№ г¶ е” ЎЄ а≠ ёс к“ о• тс ўз хЌ Ў— а∞ гі Ёё ус сщ зы пњ ч’ хЂ"\

        "цп гІ гЌ ий т“";



const char HstrL [] =

" ўы ц¶ ее кє н« ЎЁ рш бЅ бв дµ п™ кг нщ дю сЃ ф• б∞ с№ мµ пз й≠ дн ољ а•"\

        "Ёє пь пґ тл гѕ Ёх ял бј рм п© х≤ иб оо см Ўм яЈ го ч¶ ж– з– йџ ўъ сз Џ≥ х™ аѕ"\

        "№® гґ жк ађ рњ з  Ёс тџ жЋ цв оЊ ёЉ чу уї ўµ ж≤ еќ" \

        "пЃ еҐ хЈ чѓ яњ џё №¬ ме иј рЁ ў≥ иЁ ря йц џ™ бы н¬ Ё∞ а¶ у“ фѕ т√ оЇ х» ц® да"\

        " уц ё∆ сЌ цг е• м° ує зц сѕ Ёь жЃ йз йђ дт й£ №Ѓ х‘ чЋ аЏ еЉ в≤ з‘ р” о… ё§" \

        " я÷ ўэ д£ џш ёж фу хс ча яш ф‘ б„ еа к• ођ чл вё" \

        "гЅ йЁ Ёю мҐ хп ат гц №я иЏ к≤ ищ з± фб сц т» цм џє я  м÷ дѓ мЉ её жт п÷ цћ зЄ"\

        " п≥ р“ гс №„ и– зз л  н√ с™ гт рЎ";



const char HstrM [] = 

"лц сЏ ип рљ ўх ц« п≤ ар ёџ в§ лб й° пЁ ўј сІ ўщ гш №э зу ёы др ц√ яЉ ж÷ "\

        "у° бп ињ яй ц≤ Ё§ џљ т© чі ч© тэ №ђ б£ зѕ м„ п№ Џш нЋ дЁ тю ку мЄ т÷ ч÷ тъ у±"\

        " бє гч №в кƒ л£ ўу и£ о¶ нЃ ЁЃ б“ дЎ в≠ йє п— рћ дЉ "\

        "с« ч» ё— оЌ мЋ нѓ тµ Ёщ ёЂ ль нж фњ џ¬ фї тм г¬ уЈ яд мт в® чг чз ё¬ Ў¬ еф фЌ"\

        " ля фй ги еµ Џ„ а„ гж цЉ нн дѕ лп яч р≈ и¬ нр нµ зњ ег яг уъ уЇ бЇ зд №е зл з≈"\

        "г… гэ н™ ч™ №ш Џ§ дй к‘ о® х§ з— Џ” ж∆ в… чб йв №‘ пч Ёл хц сҐ п“ хш ст яи ў∞"\

        "нш ц  л§ Ўп ге џй №ў ов д≈";



const char HstrN [] = 

"ё÷ ё√ Ўњ п’ л« сƒ ёа №µ иЌ ЁЅ ЎЊ ап аЂ й™ фц ло тп ам вќ кў я≠ ЎЂ яќ н–"\

        " оу вЃ тЌ џс иІ ЏЂ џи вх ок в• цт ў£ мї к« ню ц” цу р§ йэ Ў• џю №а фЅ ж’ ле Џн"\

        "фЂ ањ т® хж ёЅ яћ сч Ўъ еЄ ж§ во бр ўѓ яж сс жџ же" \

        "еу жј оѕ н§ фђ ў– яц ёщ пї н•";



const char HstrO [] = "аё Џ© к± со вж";



const char HstrP [] =

" оў ё’ бЁ ЏҐ Ёв иЋ уб ўљ яя Ёе гЁ хз уі гъ с» сб ди ећ у¶ лг в“ бу ёЋ ре"\

        "хђ п¬ аъ мЈ аќ цђ д‘ вс аЎ №° у≤ ЎІ зҐ Џь ол аи №≈ иЅ тЈ џѓ Џр џэ оЉ тз хщ №±"\

        "вѕ Ўт џ№ я® с± дƒ ж« оҐ кґ къ фж жй лЁ хд Џ“ Ўв зќ" \

        "у™ йи о© а— жќ л≠ Ўѓ №÷ ж∞ ж… т≠ йѓ кт ж≥ ўЈ и“ ц“ о« џґ рЂ Ўѕ оё уЌ зк ёе ўц"\

        " кЈ аџ ўй и± еІ пд дя лЂ пи хл";



const char HstrQ [] =

" Ўќ с  д– бљ фт цƒ из Ё¬ а“ й  хи ЎЅ џя б™ №ќ к» сэ дњ Ёљ жл зщ зч мч т”"\

        "фл та ё≠ чҐ чи б® №ї иљ з≤ фм га №щ ЁЁ н” нђ Ё÷ чƒ Џд №Ј ўЁ б© г• н© еє еЇ ељ"\

        " о‘ тѓ ёз уй л… гї з„ №Ќ №з ўї иэ гё к® хƒ тё пЇ пѕ" \

        "пк жЌ й… ф« ся мЅ нЌ хќ Ўд зЎ №с Џџ гЊ ч≥ й‘ гЄ Џљ ж™ кь гЂ уж п∆ фј №Ћ аЇ дЏ"\

        " ая й’ ты пЈ яƒ ём ах тя цл й— чф №№ ц• уд на уј хЉ ц∆ Џц сЈ №д ућ тЋ т« й± цъ"\

        " бм т∞ ўі еѕ кд џѕ еў ф√ тш чь ф№ бЂ Џ∞ мо т– фр "\

        "чс џЊ л‘ рґ ё° нб и≥ ёЊ лђ с≥ бй уљ г÷ кп г™ Џє №х йъ оэ у№ тй ч№ о∞ зє н® г„"\

        "гЏ е“ џІ";



const char HstrR [] = 

"т≈ ч„ №џ мь р¶ №й иг жђ №у пю Ўр йн вњ с≈ лј бх б… й≈ то фџ хе чЈ п® ай"\

        " е¶ ёЄ са тђ д≤ дб з» Ёк л√ ё® №« иƒ тЄ о£ ўЉ уи";



const char HstrS [] =

" мб иЉ Ў≠ џ… ЁЎ Ўн Ў¶ м™ лџ аз лІ ф÷ вћ ёъ ня т™ з“ лэ цю №£ рю Ўƒ п§ р£"\

        "п° рр фƒ ци яю м¶ цЃ бк №ѕ ж© оћ џп фЃ х« дъ лю Џ® рё жу џЈ ж” уµ ч≠ йд хь мЎ"\

        "џр зі ув фє тў џњ ды в¶ оі ў№ Ў« д№ чк ЏЈ я” пт Џ≈ "\

        "д… лѕ й© т„ уѕ нт к… б” Ёй хІ цх вї м¬ џх Ё™ це хє мк кџ у¬ йш ож я± Џ÷ уя уІ"\

        "фЉ бч зЈ мѓ з£ ж≠ ўњ Ёƒ ёу л® пш џ” гр лт дш аІ у∞ г≈ дћ ж„ гя ещ ое а  ёч Ёф"\

        "й√ џћ я– рЄ зЅ тѕ ЎЋ п» дщ гб ўо ж¶ мл гф жб ўє" \

        "у” ск вм Џ° б¬ дЅ Ёњ б‘ г§ сµ а≤ д— в» мђ пЋ тф џ≈ а’ о§ ёі ц’ ўн д≥ Џ’ аЉ гЇ"\

        "Ёш цҐ ущ в° Ёі нх о° е° Џ« ЁЈ";



const char HstrT [] = 

"н≥ яЊ мв о„ Ўз №ж ё– хЅ ои дв ч£ гЋ еЁ йљ жж џҐ м∆ хћ цЎ ёЈ лƒ о— кЉ џ∞"\

        "сы пƒ мю ог п¶ ф  пџ вЉ дз и© йћ у• уЂ х± аы ўќ сн иЇ ч“ дђ яы Ўї мэ яѓ пЂ нЂ"\

        "лш з∞ зЊ р√ хЃ ў√ г© е— с” о± гў г√ йе ёЁ ўђ мц у‘ "\

        "цґ ти чЎ цж сї ф– Ё∆ ч— №р ж√ Ёг т— ц™ ии аћ ўЏ ў° №н н≈ ў„ дь въ чї Ё± х© о "\

        " №Ґ ЁЋ ё“ оґ еи м’ к’ вљ ла ўџ Ў± ўҐ џз гы иё н» х… хҐ й“ цЊ в’ иЎ ук";



//hstrU [] =



//hstrV [] =



const char HstrW [] =

" ўп жі Ўф лр бЋ Ўа тк жэ №є зЇ лд Ё“ зю оµ Ўи гѓ йю чЌ ўЋ е‘ Џс ЁЏ м– ё±"\

        "ан аш гн г« дґ б° бЌ мњ зв дҐ жЄ Џ√ Џу вЂ рф фЇ иЄ цџ к¶ вђ г” ц© ЎЎ гл иЈ Ёо"\

        "ё≥ ўЅ ЁЂ аЄ лњ бҐ д„ н“ цї џЎ Џщ ді тЏ чщ Ўх еь в– ви вд е√ кх рƒ Ў£ Џг иї №ћ"\

        "м… жƒ рн жр еї рЌ ц»";



const char HstrX [] =

" џ® еж ае Ё° џ„ ўв сґ џ≠ яс ё… дї м§ дј ЁЊ ф— фв фЄ р™ ў“ тб ж“ йЎ м® мд"\

        "фЋ у£ уђ хµ кЎ чы кк Џф зф бг Ёя еп Ёы мы вЊ г“ ф™ мщ бт и‘ нћ еЏ и¶ чп уЅ лѓ"\

        "мм фћ Ё≤ х— х£ ея жµ рп р¬ ўю бэ тє уЏ х– ёЇ мё б≠ №» ц± №Љ зљ Ёў жш в‘ в√ чѕ"\

        "ця у≠ и… яЎ и’ жз зѓ е– дм уп чћ б≈ уг ў…" \

        "џƒ яҐ з” з• ўф дЌ й« йњ вЁ в≥ ёѓ ев џ∆ еђ ху књ мІ №∞ цќ Ўґ Џк н  я© №ф гђ №Ї"\

        " яЁ в” рЉ хч в  чџ бґ де нм сг зп ЏЉ ит фЏ хѓ д™ џ√ д” мг ё£ Џќ ёп Ёж к— м” ўЎ" \

        "рз дц иѓ гщ м≈ оз д÷ йЄ нџ па ні хљ ч® Џ  џч сњ ві ёє к÷ хЄ бЊ вю д≠ д± №ч ца"\

        " бя ўг ";



const char HstrY [] =

" н± Ўя ив Ўу бђ зр нэ рй е¬ џл жЂ нЉ л≤ ёл вы лў б√ Ёќ дќ лз џ≥ жћ Џ• г∆"\

        "еы №Њ уџ й№ ўр ў≤ ў» Ў… џ± зь ої ч  чъ кћ мЌ дў х¶ ЏЁ ч– ЎЌ гу ч± мЊ ба м» т’"\

        "ву н¶ зџ Ў≤ яЇ Ў≥ л» йч зт бж фн ч• и√ сЇ б  рќ к„ ёё оф Џю к  м« ЏЋ Ўћ с¬ яё" \

        "вҐ м• дф аж чр џЁ Џ± вщ е∆ в¬ я„ №и кЁ нф" \

        "фэ рк бЏ о∆ №” фѓ мљ яЃ Ў„ Ўо Ўэ яљ ўЂ бї вш жд ё» ёƒ фа йу г® ёЏ џь сі зЋ рщ" \

        "тж мЏ п„ Ўж йм ё≤ фи сѓ по №≤ д¶ л≥ оч а≥ №І џу бю џі вє цЄ цѓ я≈ тЊ сЂ №б ЎЈ" \

        "ЁЇ зш а” ёь уњ иђ р– вя №г №ю Ё” йЇ дё Ёц дл ўш е≠ џЂ т£ с® лф а° зя №≠ гЉ џ’"\

        "пё чЂ бь Џƒ в≈ Ё« цІ бќ ён лй и§ км сЊ тх Ўс ўґ аф ац в„ рх сЅ цє н≤ еэ вј к≈"\

        " оЏ ЏЌ г– рЅ мѕ Ёч Ўє тв мџ р÷ еч р∞ ну уо гд лЉ цљ №Ђ йЏ уҐ џщ ж¬ ёт и• лЊ об"\

        "й– ўя еЃ з° №њ кј лµ бс йж џ© гҐ г≥ иє мў Ўь ЎЃ";



const char HstrZ [] =

" еЅ х° а© Џв я∆ ёў зё бћ фЎ фҐ к√ фх ц… иґ к∞ жа ё  яр е≈ ях аэ у– фЈ уе"\

        " Ў” Ў∆ кЊ ЏЏ з’ ој п≠ кµ яЄ яо ёк йЂ чю нƒ яе рд т∆ нќ с© мє Џё ёш џµ ж— вѓ и∞"\

        " уѓ Ўл б÷ б§ о» яъ Џѓ у… ию тЎ йь ЏЎ я° нЁ фч сё иѕ р— д• ие мх Ёи йї ур л” йф"\

        " о≥ з« р° џЏ р≤ лё кв бњ оџ п£ уЁ бз ЏЇ Ўі" \

        "иў му л’ џъ фк х≈ ёэ х№ №∆ мн ел и„ йт нй х• ве хф ащ џ§ иќ Џм ид кё йщ рЇ ей"\

        "рл тќ жп пф лщ ц£ хў ф± пс уЃ Џ£ ха ж® нЎ жы зІ л– ЁІ фь ф¶ ў™ џ• д® №п ощ й∆"\

        "ду йЌ у√ фґ рс хо дЊ чж Ўщ №— ић мƒ рж уз фг тІ ящ вЌ г№ цњ жн гЈ зƒ л∆ сЄ ўЊ"\

        " д√ нљ Ёѕ пя ўё хт зЏ яђ ё© й„ чЃ я§ Џи вф мс л— ят пц ич лк";

//}}}

// GBK „÷Јы±н э„й

// {{{

const char * g_GBK_Table [] =

{

    HstrA,

    HstrB,

    HstrC,

    HstrD,

    HstrE,

    HstrF,

    HstrG,

    HstrH,

    NULL, //HstrI,

    HstrJ,

    HstrK,

    HstrL,

    HstrM,

    HstrN,

    HstrO,

    HstrP,

    HstrQ,

    HstrR,

    HstrS,

    HstrT,

    NULL,//HstrU,

    NULL,//HstrV,

    HstrW,

    HstrX,

    HstrY,

    HstrZ,

};

//}}}



//{{{ DllEntryPoint() method

/** 

  * @brief »лњЏЇѓ э

  * 

  * @param hinst 

  * @param reason 

  * @param lpReserved 

  * 

  * @return 

  */

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)

{

    return 1;

}

//}}}



//{{{ readline() method

/** 

  * @brief і”ќƒЉю÷–ґЅ»°“ї––

  * 

  * @param fp - ґЅ»°µƒќƒЉю÷Є’л

  * @param buf - ±£іжґЅ»°µƒ эЊЁµƒїЇіж

  * @param maxlen - їЇіжµƒіу–°

  * 

  */

void __stdcall readline(FILE * fp , char * buf , int maxlen)

{

    if(fp != NULL)

    {

        int i = 0;

        int c = fgetc(fp);

        while( i < maxlen && (feof(fp) ==0) && c != '\n')

        {

            buf[i++] = (char)c;

            c = fgetc(fp);

        }

        buf[i] = '\0';

    }

}

//}}}



//{{{ LoadWbCodeTable() method

/** 

  * @brief Љ”‘Ўќе± ¬лµƒ„÷Јы±н

  * 

  * @param TablePath - „÷Јы±нµƒ¬ЈЊґ

  * 

  */

void __stdcall LoadWbCodeTable(const char * TablePath)

{

    if( TablePath == NULL )

    {

        return;

    }

    LPVOID lpAddr = AllocateMemory(BufLen);

    if (lpAddr == NULL)

        return;



    HeadWB = (PWBCodeTable)lpAddr;

    TailWB= HeadWB;



    FILE * table = fopen(TablePath,"r");

    if ( table == NULL )

        return;

        

    char line[100];

    readline(table,line,100);

    while( strlen(line) > 0 )

    {

        memset(TailWB , 0 , sizeof(WBCodeTable));

        ParseLine(TailWB, line);

        TailWB++;

        readline(table,line,100);

    }

    fclose(table);

}

//}}}



//{{{ ParseLine() method

/** 

  * @brief Ј÷ќцґЅ»°µƒ“ї–– эЊЁ,±£іжµљ„÷Јы±н

  * 

  * @param lpTbl - ±£іжµљµƒ„÷Јы±н

  * @param line - “ї–– эЊЁ

  * 

  */

void __stdcall ParseLine(PWBCodeTable lpTbl , const char * line)

{

    if (line == NULL)

        return;



    const char * start = line;

    const char * pos = line;

    int nonascii = 0;

    while(1)

    {

        if (*pos == ' ' || * pos == '\t' || *pos == '\0')

        {

            if (nonascii == 1)

            {

                int len = ((pos - start) < WB_CODE_MAX_LEN) ?

                    (pos - start) : WB_CODE_MAX_LEN;

                strncpy(lpTbl->szCode,start , len);

            }

            else if(nonascii == 2)

            {

                int len = (pos - start < WB_HZ_MAX_LEN) ?

                    (pos - start) : WB_HZ_MAX_LEN;

                strncpy(lpTbl->szHz , start , len);

                return;

            }   

            start = ++pos;

            continue;

        }

        if(isascii(*pos))

        {

            if(nonascii == 0)

            {

                start = pos;

                nonascii = 1;

            }

        }

        else

            nonascii = 2;

        pos++;

    }

}

//}}}



//{{{ GetWbCoden() method

/** 

  * @brief Љ∆Ћг÷Єґ®≥§ґ»„÷ЈыіЃµƒќе± ¬л

  * 

  * @param value - “™Љ∆Ћгќе± ¬лµƒ„÷ЈыіЃ

  * @param code - ±£іжЉ∆Ћг≥цјіµƒќе± ¬л

  * @param ctype - ±к÷Њќї

  * @param len - „÷ЈыіЃµƒ≥§ґ»

  * 

  * ±к÷Њќї : 

  * CONVERT_ALL                         ---»Ђ≤њ±£Ѕф

  * CONVERT_NO_LETTER_DIGEST            ---»•µф„÷ƒЄ, э„÷

  * CONVERT_NO_SPACE_TAB                ---»•µфњ’Єс

  * CONVERT_NO_HZ_CHAR                  ---»•µфЇЇ„÷

  * CONVERT_NO_ASCII                    ---»•µфЋщ”– ASCII „÷Јы

  */

void __stdcall GetWbCoden(const char * value, char * code ,WORD ctype, int len)

{

    if ( value == NULL )

        return;

    int i = 0;

    while( i < len)

    {

        if(isascii(value[i]))

        {

            if(value[i] == ' ' || value[i] == '\t')

            {

                if(!(ctype & CONVERT_NO_SPACE_TAB))

                    *code++ = value[i];

            }

            else

            {

                if(!(ctype & CONVERT_NO_LETTER_DIGEST))

                    *code++ = value[i];

            }

        }

        else

        {

            PWBCodeTable curr = HeadWB;

            while( curr != NULL && curr < TailWB)

            {

                if( strncmp(&value[i] , curr->szHz,2) == 0 )

                {

                    strncpy(code++, curr->szCode,1);

                    i++;

                    break;

                }

                curr++;

            }

            if( curr == TailWB && !(ctype & CONVERT_NO_HZ_CHAR))

            {

                strncpy(code, &value[i], 2);

                code += 2;

                ++i;

            }

        }

        ++i;

    }

    *code = '\0';

}

//}}}



//{{{ GetWbCode() method

/** 

  * @brief Љ∆Ћг“їЄц„÷ЈыіЃµƒќе± ¬л

  * 

  * @param value - “™Љ∆Ћгµƒ„÷ЈыіЃ

  * @param code - ±£іжЉ∆Ћг≥цµƒќе± ¬л

  * @param ctype - ±к÷Њќї

  * 

  */

void __stdcall GetWbCode(const char * value, char * code, WORD ctype)

{

    GetWbCoden(value,code,ctype,strlen(value));

}

//}}}



//{{{ GetPyCode() method

/** 

  * @brief Љ∆Ћг“їЄц„÷ЈыіЃµƒ∆і“ф¬л

  * 

  * @param value - “™Љ∆Ћгµƒ„÷ЈыіЃ

  * @param code - ±£іжЉ∆Ћгµƒ∆і“ф¬л

  * @param ctype - ±к÷Њќї

  * 

  */

void __stdcall GetPyCode(const char * value, char * code,WORD ctype)

{

    GetPyCoden(value,code,ctype,strlen(value));

}

//}}}



//{{{ GetPyCoden() method

/** 

  * @brief Љ∆Ћг“їЄц÷Єґ®≥§ґ»µƒ„÷ЈыіЃµƒ∆і“ф¬л

  * 

  * @param value - “™Љ∆Ћгµƒ„÷ЈыіЃ

  * @param code - ±£іжЉ∆Ћгµƒ∆і“ф¬л

  * @param ctype - ±к÷Њќї

  * @param len - „÷ЈыіЃµƒ≥§ґ»

  * 

  */

void __stdcall GetPyCoden(const char * value, char * code,WORD ctype, int len)

{

    if ( value == NULL )

        return;

    int i = 0;

    while( i < len)

    {

        if(isascii(value[i]))

        {

            if(value[i] == ' ' || value[i] == '\t')

            {

                if(!(ctype & CONVERT_NO_SPACE_TAB))

                    *code++ = value[i];

            }

            else

            {

                if(!(ctype & CONVERT_NO_LETTER_DIGEST))

                    *code++ = value[i];

            }

        }

        else

        {

            WORD h = value[i++];

            WORD l = value[i];

            char saveCode;

            if (h > 0x80)

            {

                WORD v = MAKEWORD(l,h);

                if( v >= 0xB0A1 && v <= 0xB0C4)

                    *code++ = 'a';

                else if (v >= 0xB0C5 && v <= 0xB2C0)

                    *code++ = 'b';

                else if (v >= 0xB2C1 && v <= 0xB4ED)

                    *code++ = 'c';

                else if (v >= 0xB4EE && v <= 0xB6E9)

                    *code++ = 'd';

                else if (v >= 0xB6EA && v <= 0xB7A1)

                    *code++ = 'e';

                else if (v >= 0xB7A2 && v <= 0xB8C0)

                    *code++ = 'f';

                else if (v >= 0xB8C1 && v <= 0xB9FD)

                    *code++ = 'g';

                else if (v >= 0xB9FE && v <= 0xBBF6)

                    *code++ = 'h';

                else if (v >= 0xBBF7 && v <= 0xBFA5)

                    *code++ = 'j';

                else if (v >= 0xBFA6 && v <= 0xC0AB)

                    *code++ = 'k';

                else if (v >= 0xC0AC && v <= 0xC2E7)

                    *code++ = 'l';

                else if (v >= 0xC2E8 && v <= 0xC4C2)

                    *code++ = 'm';

                else if (v >= 0xC4C3 && v <= 0xC5B5)

                    *code++ = 'n';

                else if (v >= 0xC5B6 && v <= 0xC5BD)

                    *code++ = 'o';

                else if (v >= 0xC5BE && v <= 0xC6D9)

                    *code++ = 'p';

                else if (v >= 0xC6DA && v <= 0xC8BA)

                    *code++ = 'q';

                else if (v >= 0xC8BB && v <= 0xC8F5)

                    *code++ = 'r';

                else if (v >= 0xC8F6 && v <= 0xCBF9)

                    *code++ = 's';

                else if (v >= 0xCBFA && v <= 0xCDD9)

                    *code++ = 't';

                else if (v >= 0xCDDA && v <= 0xCEF3)

                    *code++ = 'w';

                else if (v >= 0xCEF4 && v <= 0xD188)

                    *code++ = 'x';

                else if (v >= 0xD1B9 && v <= 0xD4D0)

                    *code++ = 'y';

                else if (v >= 0xD4D1 && v <= 0xD7F9)

                    *code++ = 'z';

                else if ( findInGBK(v,&saveCode) ) // ≈–ґѕ «Јсќ™GBK„÷Јы

                {

                    *code++ = saveCode;

                }

                else if (!(ctype & CONVERT_NO_HZ_CHAR))

                {

                    *code++ = (byte)h;

                    *code++ = (byte)l;

                }

            }

            else if(!(ctype & CONVERT_NO_HZ_CHAR))

            {

                *code++ = (byte)h;

                *code++ = (byte)l;

            }

        }

        ++i;

    }

    *code = '\0';

}

//}}}



//{{{ findInGBK() method

/** 

  * @brief ≈–ґѕ“їЄц„÷Јы «Јсќ™ GBK ЇЇ„÷

  * 

  * @param hz - „÷Јы ( ЋЂ„÷љЏ )

  * @param py - »зєы « GBK ЇЇ„÷ , ±£іжЇЇ„÷µƒ…щƒЄ

  * 

  * @return - »зєы « GBK ЇЇ„÷ ЈµїЎ÷µіу”Џ 0 , Јс‘тЈµїЎ÷µ°№ 0

  */

int __stdcall findInGBK(WORD hz , char * py)

{

    for( int i = 0;i < sizeof(g_GBK_Table) / sizeof( wchar_t * );++i )

    {

        const char * pyTbl = g_GBK_Table[i];

        const char * character = pyTbl;

        if( pyTbl == NULL )

            continue;

        while( *character != '\0' )

        {

            WORD charValue = (WORD)(*character);

            if( charValue != ' ' )

            {

                WORD lowValue = (WORD)(*(character+1));

                if( lowValue == '\0' )

                    return 0;

                charValue = MAKEWORD(lowValue,charValue);

                if( charValue == hz )

                {

                    *py = 'a' + i;

                    return 1;

                }

                character++;   

            }

            character++;

        }

        //logfile<<"find in "<<i<<endl;

    }

    return 0;

}

//}}}



//{{{ ReleaseWbCodeTable() method

/** 

  * @brief  ЌЈ≈ќе± ¬л„÷Јы±н

  * 

  * @return - »зєы≥…є¶ЈµїЎ TRUE

  */

BOOL __stdcall ReleaseWbCodeTable()

{

    CloseHandle(hGlobalFile);

    return TRUE;

}

//}}}



//{{{ AllocateMemory() method

/** 

  * @brief ‘Џ»ЂЊ÷ƒЏіж÷–…к«л“їњйƒЏіжњ’Љд

  * 

  * @param size - “™…к«лµƒњ’Љдµƒіу–°( byte )

  * 

  * @return - ЈµїЎ÷ЄѕтƒЏіжњ’Љдµƒ÷Є’л , »зєы…к«лƒЏіж І∞№ЈµїЎ NULL

  */

LPVOID __stdcall AllocateMemory(DWORD size)

{

    HANDLE hHandle = CreateFileMapping(INVALID_HANDLE_VALUE,

        NULL,

        PAGE_READWRITE,

        0,

        size,

        GlobalFileName);

    if( GetLastError() == ERROR_ALREADY_EXISTS)

    {

        return GetMemoryAddress();

    }



    if( hHandle != NULL )

    {

        hGlobalFile = hHandle;

        return GetMemoryAddress();

    }

    return NULL;

}

//}}}



//{{{ GetMemoryAddress() method

/** 

  * @brief ЈµїЎ»ЂЊ÷ƒЏіжќƒЉюµƒ÷Є’лµЎ÷Ј

  * 

  * @return - µЎ÷Ј , »зєы√ї”–…к«лƒЏіжЈµїЎ NULL

  */

LPVOID __stdcall GetMemoryAddress()

{

    if (hGlobalFile != NULL)

    {

        LPVOID lpAdd = MapViewOfFile(hGlobalFile,

            FILE_MAP_ALL_ACCESS,

            0,

            0,

            0);

        return lpAdd;

    }

    return NULL;

}

//}}}

 

