	int diametro(bintree<T> const& arbol, int& n) {
		if (arbol.empty())
			return 0;
		int left = diametro(arbol.left(), n);
		int right = diametro(arbol.right(), n);
		if (left + right >= n)
			n = left + right + 1;
		return max(right, left) + 1;
	}