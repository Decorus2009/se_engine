// код для формирования файлов статистики. Запрос("preposition [предлог]") - кол-во найденных страниц
// запись - в два файла: prepositions_stat_lexic_sort - сортировка по самим предлогам
// 						 prepositions_stat_found_sort - сортировка по числу найденных страниц.
	prepositions_dictionary PS;
	auto dict = PS.get_dictionary();

	yandex_requester YA;
	std::vector<std::pair<string, long long> > stat;

	ofstream out_file_l ("prepositions_stat_lexic_sort.txt", ios::out);
	ofstream out_file_f ("prepositions_stat_found_sort.txt", ios::out);

	vector< pair<string, long long> > v;
	for (auto it : dict) {
		// для получения статистики запрос именно: "preposition [предлог]"
		long long req_res = YA.send_request((string)"preposition " + it.first);
		cout << it.first << ' ' << req_res << endl;
		v.push_back(make_pair(it.first, req_res));
	}
	for (auto it : v) {
		out_file_l << it.first << ' ' << it.second << endl;
	}

	sort(v.begin(), v.end(), v_found_sort);

	for (auto it : v) {
		out_file_f << it.first << ' ' << it.second << endl;
	}

	out_file_l.close();
	out_file_f.close();
