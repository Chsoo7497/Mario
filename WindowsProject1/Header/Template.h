#pragma once
template<class p>
void ptr_delete(p& _ptr) {
	if (_ptr)
	{
		delete _ptr;
		_ptr = nullptr;
	}
}

