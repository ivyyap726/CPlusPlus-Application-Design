# Module 09 - Using AI to Expand Your Application

For this module, I thought about how AI could become a feature inside my Budget Tracker, not just a tool I use to write code.

**Feature I chose:** Smart Category Suggestion. When I add a new transaction, instead of typing the category every time, the AI would look at the description and my past spending to suggest a category (like "Food & Drink" or "Rent"). It could also give simple saving tips, like pointing out if I am spending a lot more than usual in one category.

**What data it needs:** My past transactions (date, category, amount) and the new transaction's description. The AI would look for patterns, like repeated keywords or amounts similar to a past category, to make its guess.

**What the user would see:** After typing the amount for a new record, the program would print something like "Suggested category: Food & Drink (press Enter to accept, or type your own)." The user can always accept the suggestion or override it, so the AI never forces a wrong answer.

**Where it fits in my application:** It sits inside `addRecord()`, between asking for the date and asking for the amount. The flow: user enters a short description → program prepares the data → AI suggests a category → program shows the suggestion → user accepts or types their own → record is saved. A live AI service is not available in my console C++ program, so I built a mock version instead: `suggestCategory()` compares keywords in the description (like "lunch" or "electric bill") against words typically seen in each of my existing categories using simple string matching, without needing a real AI model. If no keyword matches, it falls back to asking for the category normally.
