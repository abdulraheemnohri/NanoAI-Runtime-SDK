function createBadge(status) {
    const color = status === 'OK' ? 'green' : 'red';
    return `<span class="px-2 py-1 bg-${color}-500/20 text-${color}-400 text-[10px] rounded-full">SYSTEM_${status}</span>`;
}
